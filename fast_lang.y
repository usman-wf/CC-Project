%{
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

extern int yylex();
extern FILE* yyin;
extern int lineNum;
extern int tokenLineNum;
int lastValidTokenLine = 1; // Track line number of last valid token

void yyerror(const char* s);

// Symbol table and code generation
vector<string> threeAddressCode;
int tempVarCounter = 0;
int labelCounter = 0;
int parameterCount = 0;

// Helper functions for 3-address code generation
string newTemp() {
    return "t" + to_string(tempVarCounter++);
}

string newLabel() {
    return "L" + to_string(labelCounter++);
}

// Symbol table structure
struct SymbolInfo {
    string name;
    string type;
    bool isFunction;
    vector<string> paramTypes;
    SymbolInfo(const string& n, const string& t, bool f = false)
        : name(n), type(t), isFunction(f) {}
};

// Global symbol table for functions
vector<SymbolInfo> globalSymbolTable;
// Stack of symbol tables for local variables/parameters
vector<vector<SymbolInfo>> symbolTableStack;
bool hasMainFunction = false;
string currentFunctionType;
vector<string> argumentTypes;
string currentFunctionName;

// Temporary variable to store declaration type
string declType;

// Symbol table functions
void pushScope() {
    symbolTableStack.push_back(vector<SymbolInfo>());
}

void popScope() {
    if (!symbolTableStack.empty()) {
        symbolTableStack.pop_back();
    }
}

bool addSymbol(const string& name, const string& type, bool isFunction = false) {
    if (isFunction) {
        for (const auto& symbol : globalSymbolTable) {
            if (symbol.name == name) {
                return false; // Function already exists
            }
        }
        globalSymbolTable.push_back(SymbolInfo(name, type, isFunction));
        return true;
    } else {
        if (symbolTableStack.empty()) {
            pushScope();
        }
        for (const auto& symbol : symbolTableStack.back()) {
            if (symbol.name == name) {
                return false; // Symbol already exists in current scope
            }
        }
        symbolTableStack.back().push_back(SymbolInfo(name, type, isFunction));
        return true;
    }
}

SymbolInfo* findSymbol(const string& name) {
    for (auto it = symbolTableStack.rbegin(); it != symbolTableStack.rend(); ++it) {
        for (auto& symbol : *it) {
            if (symbol.name == name) {
                return &symbol;
            }
        }
    }
    for (auto& symbol : globalSymbolTable) {
        if (symbol.name == name) {
            return &symbol;
        }
    }
    return nullptr;
}

// For tracking type information during parsing
string exprType;

// Store labels for control structures
struct LoopLabels {
    string startLabel;
    string endLabel;
};

vector<LoopLabels> loopLabelsStack;
%}

%union {
    int int_val;
    bool bool_val;
    char char_val;
    char* str_val;
    char* id;
    char* expr_val;
    char* type;
    int op_val;
}

// Tokens
%token INT BOOL STRING CHAR VOID
%token IF ELSE WHILE RETURN
%token PRINT SCAN MAIN
%token ASSIGN LE GE EQ NE
%token AND OR NOT
%token ERROR

%token <int_val> INT_LITERAL
%token <bool_val> BOOL_LITERAL
%token <str_val> STRING_LITERAL
%token <char_val> CHAR_LITERAL
%token <id> ID

// Types for non-terminals
%type <expr_val> Expression AndExpr NotExpr RelationalExpr AdditiveExpr MultExpr UnaryExpr Factor FunctionCall
%type <expr_val> ArgumentList Arguments
%type <type> ReturnType BaseType
%type <op_val> RelOp
%type <op_val> AddOp
%type <op_val> MultOp

// Set precedence and associativity
%right ASSIGN
%left OR
%left AND
%right NOT
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right UNARY_MINUS

%%

Program : FunctionDeclarations MainFunction {
    if (!hasMainFunction) {
        yyerror("Error: No main function defined");
    }
    lastValidTokenLine = tokenLineNum;
}
;

MainFunction : INT MAIN '(' ')' {
    hasMainFunction = true;
    currentFunctionType = "int";
    pushScope();
    if (!addSymbol("main", "int", true)) {
        yyerror("Error: Function main already defined");
    }
    threeAddressCode.push_back("func_begin main");
    lastValidTokenLine = tokenLineNum;
} CompoundStmt {
    threeAddressCode.push_back("func_end main");
    popScope();
    lastValidTokenLine = tokenLineNum;
}
;

FunctionDeclarations : FunctionDeclarations FunctionDecl
                     | /* empty */
;

FunctionDecl : ReturnType ID {
    currentFunctionType = $1;
    currentFunctionName = $2;
    pushScope();
    if (!addSymbol($2, $1, true)) {
        string error = "Error: Function " + string($2) + " already defined";
        yyerror(error.c_str());
    }
    auto symbol = findSymbol($2);
    if (symbol) {
        symbol->paramTypes.clear();
    } else {
        string error = "Error: Failed to initialize symbol for function " + string($2);
        yyerror(error.c_str());
    }
    threeAddressCode.push_back("func_begin " + string($2));
    lastValidTokenLine = tokenLineNum;
} '(' Parameters ')' CompoundStmt {
    threeAddressCode.push_back("func_end " + currentFunctionName);
    popScope();
    lastValidTokenLine = tokenLineNum;
    free($2);
}
;

ReturnType : VOID { $$ = (char*)"void"; lastValidTokenLine = tokenLineNum; }
           | BaseType { $$ = $1; lastValidTokenLine = tokenLineNum; }
;

BaseType : INT { $$ = (char*)"int"; lastValidTokenLine = tokenLineNum; }
         | BOOL { $$ = (char*)"bool"; lastValidTokenLine = tokenLineNum; }
         | STRING { $$ = (char*)"string"; lastValidTokenLine = tokenLineNum; }
         | CHAR { $$ = (char*)"char"; lastValidTokenLine = tokenLineNum; }
;

Parameters : ParameterList
           | /* empty */
;

ParameterList : Parameter
              | ParameterList ',' Parameter
;

Parameter : BaseType ID {
    if (!addSymbol($2, $1)) {
        string error = "Error: Parameter " + string($2) + " already defined";
        yyerror(error.c_str());
    }
    auto funcSymbol = findSymbol(currentFunctionName);
    if (funcSymbol && funcSymbol->isFunction) {
        funcSymbol->paramTypes.push_back($1);
    } else {
        string error = "Error: Could not find function symbol for " + currentFunctionName;
        yyerror(error.c_str());
    }
    lastValidTokenLine = tokenLineNum;
    free($2);
}
;

CompoundStmt : '{' {
    pushScope();
    lastValidTokenLine = tokenLineNum;
} DeclsAndStmts '}' {
    popScope();
    lastValidTokenLine = tokenLineNum;
}
;

DeclsAndStmts : VarDeclaration DeclsAndStmts
              | Statement DeclsAndStmts
              | /* empty */
;

VarDeclaration : BaseType {
    declType = $1; // Store BaseType in global declType
    lastValidTokenLine = tokenLineNum;
} IdList ';' {
    declType.clear(); // Clear after use
    lastValidTokenLine = tokenLineNum;
}
;

IdList : IdInit
       | IdList ',' IdInit
;

IdInit : ID {
    if (!addSymbol($1, declType)) {
        string error = "Error: Variable " + string($1) + " already defined";
        yyerror(error.c_str());
    }
    lastValidTokenLine = tokenLineNum;
    free($1);
}
| ID ASSIGN Expression {
    if (!addSymbol($1, declType)) {
        string error = "Error: Variable " + string($1) + " already defined";
        yyerror(error.c_str());
    }
    auto symbol = findSymbol($1);
    if (symbol && !exprType.empty() && exprType != symbol->type) {
        string error = "Error: Type mismatch: cannot assign " + exprType + " to " + symbol->type + " variable " + string($1);
        yyerror(error.c_str());
    }
    string varName = $1;
    string exprTemp = $3;
    threeAddressCode.push_back(varName + " := " + exprTemp);
    lastValidTokenLine = tokenLineNum;
    free($1);
}
;

StmtList : Statement StmtList
         | /* empty */
;

Statement : ExprStmt
          | CompoundStmt
          | SelectionStmt
          | IterationStmt
          | ReturnStmt
          | IOStmt
          | FunctionCallStmt
;

FunctionCallStmt : FunctionCall ';' {
    lastValidTokenLine = tokenLineNum;
}
;

ExprStmt : ID ASSIGN Expression ';' {
    auto symbol = findSymbol($1);
    if (!symbol) {
        string error = "Error: Variable " + string($1) + " used before declaration";
        yyerror(error.c_str());
    } else if (!exprType.empty() && exprType != symbol->type) {
        string error = "Error: Type mismatch: cannot assign " + exprType + " to " + (symbol->type.empty() ? "unknown" : symbol->type) + " variable " + string($1);
        yyerror(error.c_str());
    }
    threeAddressCode.push_back(string($1) + " := " + string($3));
    lastValidTokenLine = tokenLineNum;
    free($1);
}
;

SelectionStmt : IF '(' Expression ')' Statement {
    string endLabel = newLabel();
    threeAddressCode.push_back("if " + string($3) + " == 0 goto " + endLabel);
    loopLabelsStack.push_back({"", endLabel});
    lastValidTokenLine = tokenLineNum;
} {
    threeAddressCode.push_back(loopLabelsStack.back().endLabel + ":");
    loopLabelsStack.pop_back();
    lastValidTokenLine = tokenLineNum;
}
| IF '(' Expression ')' Statement ELSE {
    string elseLabel = newLabel();
    string endLabel = newLabel();
    threeAddressCode.push_back("if " + string($3) + " == 0 goto " + elseLabel);
    loopLabelsStack.push_back({elseLabel, endLabel});
    lastValidTokenLine = tokenLineNum;
} Statement {
    threeAddressCode.push_back("goto " + loopLabelsStack.back().endLabel);
    threeAddressCode.push_back(loopLabelsStack.back().startLabel + ":");
    threeAddressCode.push_back(loopLabelsStack.back().endLabel + ":");
    loopLabelsStack.pop_back();
    lastValidTokenLine = tokenLineNum;
}
;

IterationStmt : WHILE {
    string startLabel = newLabel();
    threeAddressCode.push_back(startLabel + ":");
    loopLabelsStack.push_back({startLabel, ""});
    lastValidTokenLine = tokenLineNum;
} '(' Expression ')' {
    string endLabel = newLabel();
    threeAddressCode.push_back("if " + string($4) + " == 0 goto " + endLabel);
    loopLabelsStack.back().endLabel = endLabel;
    lastValidTokenLine = tokenLineNum;
} Statement {
    threeAddressCode.push_back("goto " + loopLabelsStack.back().startLabel);
    threeAddressCode.push_back(loopLabelsStack.back().endLabel + ":");
    loopLabelsStack.pop_back();
    lastValidTokenLine = tokenLineNum;
}
;

ReturnStmt : RETURN Expression ';' {
    if (!exprType.empty() && exprType != currentFunctionType) {
        string error = "Error: Type mismatch: cannot return " + exprType + " from " + currentFunctionType + " function";
        yyerror(error.c_str());
    }
    threeAddressCode.push_back("return " + string($2));
    lastValidTokenLine = tokenLineNum;
}
| RETURN ';' {
    if (currentFunctionType != "void") {
        yyerror("Error: Non-void function must return a value");
    }
    threeAddressCode.push_back("return");
    lastValidTokenLine = tokenLineNum;
}
;

IOStmt : PrintStmt
       | ScanStmt
;

PrintStmt : PRINT '(' Expression ')' ';' {
    threeAddressCode.push_back("param " + string($3));
    threeAddressCode.push_back("call print, 1");
    lastValidTokenLine = tokenLineNum;
}
;

ScanStmt : SCAN '(' ID ')' ';' {
    auto symbol = findSymbol($3);
    if (!symbol) {
        string error = "Error: Variable " + string($3) + " used before declaration";
        yyerror(error.c_str());
    } else {
        exprType = symbol->type;
    }
    threeAddressCode.push_back("param " + string($3));
    threeAddressCode.push_back("call scan, 1");
    lastValidTokenLine = tokenLineNum;
    free($3);
}
;

Expression : Expression OR AndExpr {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := " + string($1) + " or " + string($3));
    $$ = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
| AndExpr {
    $$ = $1;
}
;

AndExpr : AndExpr AND NotExpr {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := " + string($1) + " and " + string($3));
    $$ = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
| NotExpr {
    $$ = $1;
}
;

NotExpr : NOT NotExpr {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := not " + string($2));
    $$ = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
| RelationalExpr {
    $$ = $1;
}
;

RelationalExpr : AdditiveExpr RelOp AdditiveExpr {
    string temp = newTemp();
    string op;
    switch($2) {
        case '<': op = "<"; break;
        case '>': op = ">"; break;
        case LE: op = "<="; break;
        case GE: op = ">="; break;
        case EQ: op = "=="; break;
        case NE: op = "!="; break;
        default: op = "==";
    }
    threeAddressCode.push_back(temp + " := " + string($1) + " " + op + " " + string($3));
    $$ = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
| AdditiveExpr {
    $$ = $1;
}
;

RelOp : '<' { $$ = '<'; lastValidTokenLine = tokenLineNum; }
      | '>' { $$ = '>'; lastValidTokenLine = tokenLineNum; }
      | LE { $$ = LE; lastValidTokenLine = tokenLineNum; }
      | GE { $$ = GE; lastValidTokenLine = tokenLineNum; }
      | EQ { $$ = EQ; lastValidTokenLine = tokenLineNum; }
      | NE { $$ = NE; lastValidTokenLine = tokenLineNum; }
;

AdditiveExpr : AdditiveExpr AddOp MultExpr {
    if (exprType != "int") {
        string error = "Error: Arithmetic operation requires int operands, got " + (exprType.empty() ? "unknown" : exprType);
        yyerror(error.c_str());
    }
    string temp = newTemp();
    char op = (char)$2;
    threeAddressCode.push_back(temp + " := " + string($1) + " " + op + " " + string($3));
    $$ = _strdup(temp.c_str());
    exprType = "int";
    lastValidTokenLine = tokenLineNum;
}
| MultExpr {
    $$ = $1;
}
;

AddOp : '+' { $$ = '+'; lastValidTokenLine = tokenLineNum; }
      | '-' { $$ = '-'; lastValidTokenLine = tokenLineNum; }
;

MultExpr : MultExpr MultOp UnaryExpr {
    if (exprType != "int") {
        string error = "Error: Arithmetic operation requires int operands, got " + (exprType.empty() ? "unknown" : exprType);
        yyerror(error.c_str());
    }
    string temp = newTemp();
    char op = (char)$2;
    threeAddressCode.push_back(temp + " := " + string($1) + " " + op + " " + string($3));
    $$ = _strdup(temp.c_str());
    exprType = "int";
    lastValidTokenLine = tokenLineNum;
}
| UnaryExpr {
    $$ = $1;
}
;

MultOp : '*' { $$ = '*'; lastValidTokenLine = tokenLineNum; }
       | '/' { $$ = '/'; lastValidTokenLine = tokenLineNum; }
       | '%' { $$ = '%'; lastValidTokenLine = tokenLineNum; }
;

UnaryExpr : '-' Factor %prec UNARY_MINUS {
    if (exprType != "int") {
        string error = "Error: Unary minus requires int operand, got " + (exprType.empty() ? "unknown" : exprType);
        yyerror(error.c_str());
    }
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := -" + string($2));
    $$ = _strdup(temp.c_str());
    exprType = "int";
    lastValidTokenLine = tokenLineNum;
}
| Factor {
    $$ = $1;
}
;

Factor : INT_LITERAL {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := " + to_string($1));
    $$ = _strdup(temp.c_str());
    exprType = "int";
    lastValidTokenLine = tokenLineNum;
}
| BOOL_LITERAL {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := " + ($1 ? "true" : "false"));
    $$ = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
| STRING_LITERAL {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := \"" + string($1) + "\"");
    $$ = _strdup(temp.c_str());
    exprType = "string";
    lastValidTokenLine = tokenLineNum;
    free($1);
}
| CHAR_LITERAL {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := '" + string(1, $1) + "'");
    $$ = _strdup(temp.c_str());
    exprType = "char";
    lastValidTokenLine = tokenLineNum;
}
| FunctionCall {
    $$ = $1;
}
| ID {
    auto symbol = findSymbol($1);
    if (!symbol) {
        string error = "Error: Variable " + string($1) + " used before declaration";
        yyerror(error.c_str());
        exprType = "unknown";
    } else if (symbol->isFunction) {
        string error = "Error: " + string($1) + " is not a variable";
        yyerror(error.c_str());
        exprType = "unknown";
    } else {
        exprType = symbol->type.empty() ? "unknown" : symbol->type;
    }
    $$ = _strdup($1);
    lastValidTokenLine = tokenLineNum;
    free($1);
}
| '(' Expression ')' {
    $$ = $2;
    lastValidTokenLine = tokenLineNum;
}
;

FunctionCall : ID '(' {
    parameterCount = 0;
    argumentTypes.clear();
    lastValidTokenLine = tokenLineNum;
} Arguments ')' {
    auto symbol = findSymbol($1);
    if (!symbol) {
        string error = "Error: Function " + string($1) + " used before declaration";
        yyerror(error.c_str());
        exprType = "unknown";
    } else if (!symbol->isFunction) {
        string error = "Error: " + string($1) + " is not a function";
        yyerror(error.c_str());
        exprType = "unknown";
    } else if (symbol->paramTypes.size() != parameterCount) {
        string error = "Error: Function " + string($1) + " expects " +
                       to_string(symbol->paramTypes.size()) + " arguments, got " +
                       to_string(parameterCount);
        yyerror(error.c_str());
        exprType = "unknown";
    } else {
        for (size_t i = 0; i < parameterCount; ++i) {
            if (!argumentTypes[i].empty() && argumentTypes[i] != symbol->paramTypes[i]) {
                string error = "Error: Type mismatch: argument " + to_string(i + 1) +
                               " of " + string($1) + " expects " + symbol->paramTypes[i] +
                               ", got " + (argumentTypes[i].empty() ? "unknown" : argumentTypes[i]);
                yyerror(error.c_str());
            }
        }
        exprType = symbol->type.empty() ? "unknown" : symbol->type;
    }
    threeAddressCode.push_back("call " + string($1) + ", " + to_string(parameterCount));
    string temp;
    if (symbol && symbol->type != "void") {
        temp = newTemp();
        threeAddressCode.push_back(temp + " := return_value");
    }
    $$ = _strdup(temp.c_str());
    lastValidTokenLine = tokenLineNum;
    free($1);
}
;

Arguments : ArgumentList {
    $$ = $1;
}
| /* empty */ {
    $$ = _strdup("");
}
;

ArgumentList : ArgumentList ',' Expression {
    threeAddressCode.push_back("param " + string($3));
    argumentTypes.push_back(exprType.empty() ? "unknown" : exprType);
    parameterCount++;
    $$ = _strdup(""); // Just a placeholder
    lastValidTokenLine = tokenLineNum;
}
| Expression {
    threeAddressCode.push_back("param " + string($1));
    argumentTypes.push_back(exprType.empty() ? "unknown" : exprType);
    parameterCount = 1;
    $$ = _strdup(""); // Just a placeholder
    lastValidTokenLine = tokenLineNum;
}
;

%%

void yyerror(const char* s) {
    cerr << "Error at line " << lastValidTokenLine << ": " << s << endl;
}