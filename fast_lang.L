%{
#include <string>
#include <iostream>
#include "fast_lang.tab.h"

using namespace std;

extern int yyerror(const char* msg);
extern int lineNum;
extern int tokenLineNum; // Track token line number
int lineNum = 1;
int tokenLineNum = 1; // Initialize to 1

// For string literal handling
string string_buffer;
%}

%option noyywrap

/* States for handling string literals and comments */
%x STRING_STATE
%x CHAR_STATE
%x SINGLE_COMMENT
%x MULTI_COMMENT

%%

    /* Keywords */
"int"       { tokenLineNum = lineNum; return INT; }
"bool"      { tokenLineNum = lineNum; return BOOL; }
"string"    { tokenLineNum = lineNum; return STRING; }
"char"      { tokenLineNum = lineNum; return CHAR; }
"if"        { tokenLineNum = lineNum; return IF; }
"else"      { tokenLineNum = lineNum; return ELSE; }
"while"     { tokenLineNum = lineNum; return WHILE; }
"return"    { tokenLineNum = lineNum; return RETURN; }
"true"      { tokenLineNum = lineNum; yylval.bool_val = true; return BOOL_LITERAL; }
"false"     { tokenLineNum = lineNum; yylval.bool_val = false; return BOOL_LITERAL; }
"and"       { tokenLineNum = lineNum; return AND; }
"or"        { tokenLineNum = lineNum; return OR; }
"not"       { tokenLineNum = lineNum; return NOT; }
"void"      { tokenLineNum = lineNum; return VOID; }
"print"     { tokenLineNum = lineNum; return PRINT; }
"scan"      { tokenLineNum = lineNum; return SCAN; }
"main"      { tokenLineNum = lineNum; return MAIN; }

    /* Identifiers */
[A-Za-z][A-Za-z0-9_]*  { 
    tokenLineNum = lineNum; 
    yylval.id = _strdup(yytext); 
    return ID; 
}

    /* Integer literals */
[0-9]+  { 
    tokenLineNum = lineNum; 
    yylval.int_val = atoi(yytext); 
    return INT_LITERAL; 
}

    /* String literals */
\"      { 
    tokenLineNum = lineNum; 
    string_buffer.clear(); 
    BEGIN(STRING_STATE); 
}

<STRING_STATE>\"    { 
    tokenLineNum = lineNum; 
    BEGIN(INITIAL); 
    yylval.str_val = _strdup(string_buffer.c_str()); 
    return STRING_LITERAL; 
}

<STRING_STATE>\n    { 
    lineNum++; 
    string_buffer += '\n'; 
}

<STRING_STATE>\\\"  { string_buffer += '\"'; }
<STRING_STATE>\\n   { string_buffer += '\n'; }
<STRING_STATE>\\t   { string_buffer += '\t'; }
<STRING_STATE>\\\\  { string_buffer += '\\'; }
<STRING_STATE>.     { string_buffer += yytext[0]; }

    /* Character literals */
\'      { 
    tokenLineNum = lineNum; 
    BEGIN(CHAR_STATE); 
}

<CHAR_STATE>\'    { 
    tokenLineNum = lineNum; 
    BEGIN(INITIAL); 
    return CHAR_LITERAL; 
}

<CHAR_STATE>\\\'  { yylval.char_val = '\''; }
<CHAR_STATE>\\n   { yylval.char_val = '\n'; }
<CHAR_STATE>\\t   { yylval.char_val = '\t'; }
<CHAR_STATE>\\\\  { yylval.char_val = '\\'; }
<CHAR_STATE>.     { yylval.char_val = yytext[0]; }

    /* Operators */
"+"     { tokenLineNum = lineNum; return '+'; }
"-"     { tokenLineNum = lineNum; return '-'; }
"*"     { tokenLineNum = lineNum; return '*'; }
"/"     { tokenLineNum = lineNum; return '/'; }
"%"     { tokenLineNum = lineNum; return '%'; }
":="    { tokenLineNum = lineNum; return ASSIGN; }
"<"     { tokenLineNum = lineNum; return '<'; }
">"     { tokenLineNum = lineNum; return '>'; }
"<="    { tokenLineNum = lineNum; return LE; }
">="    { tokenLineNum = lineNum; return GE; }
"=="    { tokenLineNum = lineNum; return EQ; }
"!="    { tokenLineNum = lineNum; return NE; }

    /* Delimiters */
";"     { tokenLineNum = lineNum; return ';'; }
","     { tokenLineNum = lineNum; return ','; }
"{"     { tokenLineNum = lineNum; return '{'; }
"}"     { tokenLineNum = lineNum; return '}'; }
"("     { tokenLineNum = lineNum; return '('; }
")"     { tokenLineNum = lineNum; return ')'; }

    /* Comments */
"//"    { tokenLineNum = lineNum; BEGIN(SINGLE_COMMENT); }
<SINGLE_COMMENT>\n    { 
    lineNum++; 
    BEGIN(INITIAL); 
}
<SINGLE_COMMENT>.     { /* Ignore comment content */ }

"/*"    { tokenLineNum = lineNum; BEGIN(MULTI_COMMENT); }
<MULTI_COMMENT>"*/"   { tokenLineNum = lineNum; BEGIN(INITIAL); }
<MULTI_COMMENT>\n     { lineNum++; }
<MULTI_COMMENT>.      { /* Ignore comment content */ }

    /* Whitespace */
[ \t]+  { /* Ignore whitespace */ }
\n      { lineNum++; }

    /* Error handling */
.       { 
    tokenLineNum = lineNum; 
    cerr << "Error: Unexpected character '" << yytext << "' at line " << tokenLineNum << endl; 
    return ERROR; 
}

%%