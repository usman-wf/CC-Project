/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "fast_lang.y"

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

/* Line 371 of yacc.c  */
#line 183 "fast_lang.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "fast_lang.tab.h".  */
#ifndef YY_YY_FAST_LANG_TAB_H_INCLUDED
# define YY_YY_FAST_LANG_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     BOOL = 259,
     STRING = 260,
     CHAR = 261,
     VOID = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     RETURN = 266,
     PRINT = 267,
     SCAN = 268,
     MAIN = 269,
     ASSIGN = 270,
     LE = 271,
     GE = 272,
     EQ = 273,
     NE = 274,
     AND = 275,
     OR = 276,
     NOT = 277,
     ERROR = 278,
     INT_LITERAL = 279,
     BOOL_LITERAL = 280,
     STRING_LITERAL = 281,
     CHAR_LITERAL = 282,
     ID = 283,
     UNARY_MINUS = 284
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 116 "fast_lang.y"

    int int_val;
    bool bool_val;
    char char_val;
    char* str_val;
    char* id;
    char* expr_val;
    char* type;
    int op_val;


/* Line 387 of yacc.c  */
#line 267 "fast_lang.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_FAST_LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 295 "fast_lang.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   147

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNRULES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    35,     2,     2,
      37,    38,    33,    31,    39,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
      29,     2,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    17,    18,    19,    27,
      29,    31,    33,    35,    37,    39,    41,    42,    44,    48,
      51,    52,    57,    60,    63,    64,    65,    70,    72,    76,
      78,    82,    84,    86,    88,    90,    92,    94,    96,    99,
     104,   105,   112,   113,   122,   123,   124,   132,   136,   139,
     141,   143,   149,   155,   159,   161,   165,   167,   170,   172,
     176,   178,   180,   182,   184,   186,   188,   190,   194,   196,
     198,   200,   204,   206,   208,   210,   212,   215,   217,   219,
     221,   223,   225,   227,   229,   233,   234,   240,   242,   243,
     247
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    47,    45,    -1,    -1,     3,    14,    37,
      38,    46,    55,    -1,    47,    48,    -1,    -1,    -1,    50,
      28,    49,    37,    52,    38,    55,    -1,     7,    -1,    51,
      -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,    53,
      -1,    -1,    54,    -1,    53,    39,    54,    -1,    51,    28,
      -1,    -1,    40,    56,    57,    41,    -1,    58,    57,    -1,
      62,    57,    -1,    -1,    -1,    51,    59,    60,    42,    -1,
      61,    -1,    60,    39,    61,    -1,    28,    -1,    28,    15,
      75,    -1,    64,    -1,    55,    -1,    65,    -1,    68,    -1,
      71,    -1,    72,    -1,    63,    -1,    86,    42,    -1,    28,
      15,    75,    42,    -1,    -1,     8,    37,    75,    38,    62,
      66,    -1,    -1,     8,    37,    75,    38,    62,     9,    67,
      62,    -1,    -1,    -1,    10,    69,    37,    75,    38,    70,
      62,    -1,    11,    75,    42,    -1,    11,    42,    -1,    73,
      -1,    74,    -1,    12,    37,    75,    38,    42,    -1,    13,
      37,    28,    38,    42,    -1,    75,    21,    76,    -1,    76,
      -1,    76,    20,    77,    -1,    77,    -1,    22,    77,    -1,
      78,    -1,    80,    79,    80,    -1,    80,    -1,    29,    -1,
      30,    -1,    16,    -1,    17,    -1,    18,    -1,    19,    -1,
      80,    81,    82,    -1,    82,    -1,    31,    -1,    32,    -1,
      82,    83,    84,    -1,    84,    -1,    33,    -1,    34,    -1,
      35,    -1,    32,    85,    -1,    85,    -1,    24,    -1,    25,
      -1,    26,    -1,    27,    -1,    86,    -1,    28,    -1,    37,
      75,    38,    -1,    -1,    28,    37,    87,    88,    38,    -1,
      89,    -1,    -1,    89,    39,    75,    -1,    75,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   170,   170,   186,   187,   190,   190,   215,
     216,   219,   220,   221,   222,   225,   226,   229,   230,   233,
     250,   250,   259,   260,   261,   264,   264,   273,   274,   277,
     285,   307,   308,   309,   310,   311,   312,   313,   316,   321,
     336,   336,   346,   346,   361,   366,   361,   379,   387,   396,
     397,   400,   407,   422,   429,   434,   441,   446,   453,   458,
     475,   480,   481,   482,   483,   484,   485,   488,   500,   505,
     506,   509,   521,   526,   527,   528,   531,   542,   547,   554,
     561,   569,   576,   579,   596,   602,   602,   645,   648,   653,
     660
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "BOOL", "STRING", "CHAR", "VOID",
  "IF", "ELSE", "WHILE", "RETURN", "PRINT", "SCAN", "MAIN", "ASSIGN", "LE",
  "GE", "EQ", "NE", "AND", "OR", "NOT", "ERROR", "INT_LITERAL",
  "BOOL_LITERAL", "STRING_LITERAL", "CHAR_LITERAL", "ID", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "UNARY_MINUS", "'('", "')'", "','",
  "'{'", "'}'", "';'", "$accept", "Program", "MainFunction", "$@1",
  "FunctionDeclarations", "FunctionDecl", "$@2", "ReturnType", "BaseType",
  "Parameters", "ParameterList", "Parameter", "CompoundStmt", "$@3",
  "DeclsAndStmts", "VarDeclaration", "$@4", "IdList", "IdInit",
  "Statement", "FunctionCallStmt", "ExprStmt", "SelectionStmt", "$@5",
  "$@6", "IterationStmt", "$@7", "$@8", "ReturnStmt", "IOStmt",
  "PrintStmt", "ScanStmt", "Expression", "AndExpr", "NotExpr",
  "RelationalExpr", "RelOp", "AdditiveExpr", "AddOp", "MultExpr", "MultOp",
  "UnaryExpr", "Factor", "FunctionCall", "$@9", "Arguments",
  "ArgumentList", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    60,
      62,    43,    45,    42,    47,    37,   284,    40,    41,    44,
     123,   125,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    46,    45,    47,    47,    49,    48,    50,
      50,    51,    51,    51,    51,    52,    52,    53,    53,    54,
      56,    55,    57,    57,    57,    59,    58,    60,    60,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    63,    64,
      66,    65,    67,    65,    69,    70,    68,    71,    71,    72,
      72,    73,    74,    75,    75,    76,    76,    77,    77,    78,
      78,    79,    79,    79,    79,    79,    79,    80,    80,    81,
      81,    82,    82,    83,    83,    83,    84,    84,    85,    85,
      85,    85,    85,    85,    85,    87,    86,    88,    88,    89,
      89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     2,     0,     0,     7,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     3,     2,
       0,     4,     2,     2,     0,     0,     4,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     4,
       0,     6,     0,     8,     0,     0,     7,     3,     2,     1,
       1,     5,     5,     3,     1,     3,     1,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     5,     1,     0,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     1,    11,    12,    13,    14,     9,     2,
       5,     0,    10,     0,     7,     0,     0,     3,    16,     0,
      11,     0,     0,    15,    17,    20,     4,    19,     0,     0,
      24,     8,    18,     0,    44,     0,     0,     0,     0,    25,
      32,     0,    24,    24,    37,    31,    33,    34,    35,    36,
      49,    50,     0,     0,     0,     0,    78,    79,    80,    81,
      83,     0,     0,    48,     0,    54,    56,    58,    60,    68,
      72,    77,    82,     0,     0,     0,    85,     0,    21,    22,
      23,    38,     0,     0,    57,    76,     0,     0,    47,     0,
      63,    64,    65,    66,    61,    62,    69,    70,     0,     0,
      73,    74,    75,     0,     0,     0,     0,    88,    29,     0,
      27,     0,     0,    84,    53,    55,    59,    67,    71,     0,
       0,    39,    90,     0,    87,     0,     0,    26,    40,    45,
      51,    52,    86,     0,    30,    28,    42,    41,     0,    89,
       0,    46,    43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     9,    19,     2,    10,    16,    11,    39,    22,
      23,    24,    40,    30,    41,    42,    77,   109,   110,    43,
      44,    45,    46,   137,   140,    47,    54,   138,    48,    49,
      50,    51,    64,    65,    66,    67,    98,    68,    99,    69,
     103,    70,    71,    72,   107,   123,   124
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -108
static const yytype_int16 yypact[] =
{
    -108,     3,   119,  -108,    50,  -108,  -108,  -108,  -108,  -108,
    -108,    40,  -108,    32,  -108,    41,    43,  -108,    95,    48,
    -108,    66,    57,    70,  -108,  -108,  -108,  -108,    48,    95,
      15,  -108,  -108,    59,  -108,    25,    75,    76,    -8,  -108,
    -108,    73,    15,    15,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,    36,    65,    78,    65,  -108,  -108,  -108,  -108,
      90,    93,    65,  -108,    19,   108,  -108,  -108,    54,    11,
    -108,  -108,  -108,    65,   101,    65,  -108,   103,  -108,  -108,
    -108,  -108,    27,    65,  -108,  -108,    37,    65,  -108,    65,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,    79,    79,
    -108,  -108,  -108,    79,    38,    94,    21,    65,   118,   -34,
    -108,    26,    39,  -108,   108,  -108,   -22,    11,  -108,    92,
      96,  -108,   114,    98,   100,    65,   103,  -108,   128,  -108,
    -108,  -108,  -108,    65,   114,  -108,  -108,  -108,    26,   114,
      26,  -108,  -108
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,    12,  -108,
    -108,   111,   -13,  -108,   -26,  -108,  -108,  -108,    16,  -107,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,   -51,    56,   -54,  -108,  -108,    46,  -108,    42,
    -108,    44,    84,   -30,  -108,  -108,  -108
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      52,    84,    82,     3,   128,   126,    26,    75,   127,    96,
      97,    86,    52,    52,    12,    31,    79,    80,    20,     5,
       6,     7,   104,    33,   106,    34,    35,    36,    37,    76,
      21,   141,   112,   142,    33,   115,    34,    35,    36,    37,
      87,    21,    87,    38,   100,   101,   102,    55,    87,    56,
      57,    58,    59,    60,    38,    25,   122,    61,    87,    87,
      87,    88,    62,   121,    13,   111,    25,    63,    14,    15,
      90,    91,    92,    93,   134,   113,   119,   129,    81,    17,
      18,    52,   139,    94,    95,    96,    97,    55,    25,    56,
      57,    58,    59,    60,    27,    28,    53,    61,    20,     5,
       6,     7,    62,    56,    57,    58,    59,    60,    52,    29,
      52,    61,    73,    74,    78,    83,    62,    56,    57,    58,
      59,    60,     4,     5,     6,     7,     8,    76,    89,   105,
      62,   108,   120,   125,   130,    87,   132,   136,   131,   133,
      32,   117,   135,   114,   116,    85,     0,   118
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-108)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      30,    55,    53,     0,   111,    39,    19,    15,    42,    31,
      32,    62,    42,    43,     2,    28,    42,    43,     3,     4,
       5,     6,    73,     8,    75,    10,    11,    12,    13,    37,
      18,   138,    83,   140,     8,    89,    10,    11,    12,    13,
      21,    29,    21,    28,    33,    34,    35,    22,    21,    24,
      25,    26,    27,    28,    28,    40,   107,    32,    21,    21,
      21,    42,    37,    42,    14,    38,    40,    42,    28,    37,
      16,    17,    18,    19,   125,    38,    38,    38,    42,    38,
      37,   111,   133,    29,    30,    31,    32,    22,    40,    24,
      25,    26,    27,    28,    28,    38,    37,    32,     3,     4,
       5,     6,    37,    24,    25,    26,    27,    28,   138,    39,
     140,    32,    37,    37,    41,    37,    37,    24,    25,    26,
      27,    28,     3,     4,     5,     6,     7,    37,    20,    28,
      37,    28,    38,    15,    42,    21,    38,     9,    42,    39,
      29,    99,   126,    87,    98,    61,    -1,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    47,     0,     3,     4,     5,     6,     7,    45,
      48,    50,    51,    14,    28,    37,    49,    38,    37,    46,
       3,    51,    52,    53,    54,    40,    55,    28,    38,    39,
      56,    55,    54,     8,    10,    11,    12,    13,    28,    51,
      55,    57,    58,    62,    63,    64,    65,    68,    71,    72,
      73,    74,    86,    37,    69,    22,    24,    25,    26,    27,
      28,    32,    37,    42,    75,    76,    77,    78,    80,    82,
      84,    85,    86,    37,    37,    15,    37,    59,    41,    57,
      57,    42,    75,    37,    77,    85,    75,    21,    42,    20,
      16,    17,    18,    19,    29,    30,    31,    32,    79,    81,
      33,    34,    35,    83,    75,    28,    75,    87,    28,    60,
      61,    38,    75,    38,    76,    77,    80,    82,    84,    38,
      38,    42,    75,    88,    89,    15,    39,    42,    62,    38,
      42,    42,    38,    39,    75,    61,     9,    66,    70,    75,
      67,    62,    62
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 162 "fast_lang.y"
    {
    if (!hasMainFunction) {
        yyerror("Error: No main function defined");
    }
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 170 "fast_lang.y"
    {
    hasMainFunction = true;
    currentFunctionType = "int";
    pushScope();
    if (!addSymbol("main", "int", true)) {
        yyerror("Error: Function main already defined");
    }
    threeAddressCode.push_back("func_begin main");
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 179 "fast_lang.y"
    {
    threeAddressCode.push_back("func_end main");
    popScope();
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 190 "fast_lang.y"
    {
    currentFunctionType = (yyvsp[(1) - (2)].type);
    currentFunctionName = (yyvsp[(2) - (2)].id);
    pushScope();
    if (!addSymbol((yyvsp[(2) - (2)].id), (yyvsp[(1) - (2)].type), true)) {
        string error = "Error: Function " + string((yyvsp[(2) - (2)].id)) + " already defined";
        yyerror(error.c_str());
    }
    auto symbol = findSymbol((yyvsp[(2) - (2)].id));
    if (symbol) {
        symbol->paramTypes.clear();
    } else {
        string error = "Error: Failed to initialize symbol for function " + string((yyvsp[(2) - (2)].id));
        yyerror(error.c_str());
    }
    threeAddressCode.push_back("func_begin " + string((yyvsp[(2) - (2)].id)));
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 207 "fast_lang.y"
    {
    threeAddressCode.push_back("func_end " + currentFunctionName);
    popScope();
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(2) - (7)].id));
}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 215 "fast_lang.y"
    { (yyval.type) = (char*)"void"; lastValidTokenLine = tokenLineNum; }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 216 "fast_lang.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); lastValidTokenLine = tokenLineNum; }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 219 "fast_lang.y"
    { (yyval.type) = (char*)"int"; lastValidTokenLine = tokenLineNum; }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 220 "fast_lang.y"
    { (yyval.type) = (char*)"bool"; lastValidTokenLine = tokenLineNum; }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 221 "fast_lang.y"
    { (yyval.type) = (char*)"string"; lastValidTokenLine = tokenLineNum; }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 222 "fast_lang.y"
    { (yyval.type) = (char*)"char"; lastValidTokenLine = tokenLineNum; }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 233 "fast_lang.y"
    {
    if (!addSymbol((yyvsp[(2) - (2)].id), (yyvsp[(1) - (2)].type))) {
        string error = "Error: Parameter " + string((yyvsp[(2) - (2)].id)) + " already defined";
        yyerror(error.c_str());
    }
    auto funcSymbol = findSymbol(currentFunctionName);
    if (funcSymbol && funcSymbol->isFunction) {
        funcSymbol->paramTypes.push_back((yyvsp[(1) - (2)].type));
    } else {
        string error = "Error: Could not find function symbol for " + currentFunctionName;
        yyerror(error.c_str());
    }
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(2) - (2)].id));
}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 250 "fast_lang.y"
    {
    pushScope();
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 253 "fast_lang.y"
    {
    popScope();
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 264 "fast_lang.y"
    {
    declType = (yyvsp[(1) - (1)].type); // Store BaseType in global declType
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 267 "fast_lang.y"
    {
    declType.clear(); // Clear after use
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 277 "fast_lang.y"
    {
    if (!addSymbol((yyvsp[(1) - (1)].id), declType)) {
        string error = "Error: Variable " + string((yyvsp[(1) - (1)].id)) + " already defined";
        yyerror(error.c_str());
    }
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(1) - (1)].id));
}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 285 "fast_lang.y"
    {
    if (!addSymbol((yyvsp[(1) - (3)].id), declType)) {
        string error = "Error: Variable " + string((yyvsp[(1) - (3)].id)) + " already defined";
        yyerror(error.c_str());
    }
    auto symbol = findSymbol((yyvsp[(1) - (3)].id));
    if (symbol && !exprType.empty() && exprType != symbol->type) {
        string error = "Error: Type mismatch: cannot assign " + exprType + " to " + symbol->type + " variable " + string((yyvsp[(1) - (3)].id));
        yyerror(error.c_str());
    }
    string varName = (yyvsp[(1) - (3)].id);
    string exprTemp = (yyvsp[(3) - (3)].expr_val);
    threeAddressCode.push_back(varName + " := " + exprTemp);
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(1) - (3)].id));
}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 316 "fast_lang.y"
    {
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 321 "fast_lang.y"
    {
    auto symbol = findSymbol((yyvsp[(1) - (4)].id));
    if (!symbol) {
        string error = "Error: Variable " + string((yyvsp[(1) - (4)].id)) + " used before declaration";
        yyerror(error.c_str());
    } else if (!exprType.empty() && exprType != symbol->type) {
        string error = "Error: Type mismatch: cannot assign " + exprType + " to " + (symbol->type.empty() ? "unknown" : symbol->type) + " variable " + string((yyvsp[(1) - (4)].id));
        yyerror(error.c_str());
    }
    threeAddressCode.push_back(string((yyvsp[(1) - (4)].id)) + " := " + string((yyvsp[(3) - (4)].expr_val)));
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(1) - (4)].id));
}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 336 "fast_lang.y"
    {
    string endLabel = newLabel();
    threeAddressCode.push_back("if " + string((yyvsp[(3) - (5)].expr_val)) + " == 0 goto " + endLabel);
    loopLabelsStack.push_back({"", endLabel});
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 341 "fast_lang.y"
    {
    threeAddressCode.push_back(loopLabelsStack.back().endLabel + ":");
    loopLabelsStack.pop_back();
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 346 "fast_lang.y"
    {
    string elseLabel = newLabel();
    string endLabel = newLabel();
    threeAddressCode.push_back("if " + string((yyvsp[(3) - (6)].expr_val)) + " == 0 goto " + elseLabel);
    loopLabelsStack.push_back({elseLabel, endLabel});
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 352 "fast_lang.y"
    {
    threeAddressCode.push_back("goto " + loopLabelsStack.back().endLabel);
    threeAddressCode.push_back(loopLabelsStack.back().startLabel + ":");
    threeAddressCode.push_back(loopLabelsStack.back().endLabel + ":");
    loopLabelsStack.pop_back();
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 361 "fast_lang.y"
    {
    string startLabel = newLabel();
    threeAddressCode.push_back(startLabel + ":");
    loopLabelsStack.push_back({startLabel, ""});
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 366 "fast_lang.y"
    {
    string endLabel = newLabel();
    threeAddressCode.push_back("if " + string((yyvsp[(4) - (5)].expr_val)) + " == 0 goto " + endLabel);
    loopLabelsStack.back().endLabel = endLabel;
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 371 "fast_lang.y"
    {
    threeAddressCode.push_back("goto " + loopLabelsStack.back().startLabel);
    threeAddressCode.push_back(loopLabelsStack.back().endLabel + ":");
    loopLabelsStack.pop_back();
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 379 "fast_lang.y"
    {
    if (!exprType.empty() && exprType != currentFunctionType) {
        string error = "Error: Type mismatch: cannot return " + exprType + " from " + currentFunctionType + " function";
        yyerror(error.c_str());
    }
    threeAddressCode.push_back("return " + string((yyvsp[(2) - (3)].expr_val)));
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 387 "fast_lang.y"
    {
    if (currentFunctionType != "void") {
        yyerror("Error: Non-void function must return a value");
    }
    threeAddressCode.push_back("return");
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 400 "fast_lang.y"
    {
    threeAddressCode.push_back("param " + string((yyvsp[(3) - (5)].expr_val)));
    threeAddressCode.push_back("call print, 1");
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 407 "fast_lang.y"
    {
    auto symbol = findSymbol((yyvsp[(3) - (5)].id));
    if (!symbol) {
        string error = "Error: Variable " + string((yyvsp[(3) - (5)].id)) + " used before declaration";
        yyerror(error.c_str());
    } else {
        exprType = symbol->type;
    }
    threeAddressCode.push_back("param " + string((yyvsp[(3) - (5)].id)));
    threeAddressCode.push_back("call scan, 1");
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(3) - (5)].id));
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 422 "fast_lang.y"
    {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := " + string((yyvsp[(1) - (3)].expr_val)) + " or " + string((yyvsp[(3) - (3)].expr_val)));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 429 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 434 "fast_lang.y"
    {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := " + string((yyvsp[(1) - (3)].expr_val)) + " and " + string((yyvsp[(3) - (3)].expr_val)));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 441 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 446 "fast_lang.y"
    {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := not " + string((yyvsp[(2) - (2)].expr_val)));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 453 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 458 "fast_lang.y"
    {
    string temp = newTemp();
    string op;
    switch((yyvsp[(2) - (3)].op_val)) {
        case '<': op = "<"; break;
        case '>': op = ">"; break;
        case LE: op = "<="; break;
        case GE: op = ">="; break;
        case EQ: op = "=="; break;
        case NE: op = "!="; break;
        default: op = "==";
    }
    threeAddressCode.push_back(temp + " := " + string((yyvsp[(1) - (3)].expr_val)) + " " + op + " " + string((yyvsp[(3) - (3)].expr_val)));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 475 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 480 "fast_lang.y"
    { (yyval.op_val) = '<'; lastValidTokenLine = tokenLineNum; }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 481 "fast_lang.y"
    { (yyval.op_val) = '>'; lastValidTokenLine = tokenLineNum; }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 482 "fast_lang.y"
    { (yyval.op_val) = LE; lastValidTokenLine = tokenLineNum; }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 483 "fast_lang.y"
    { (yyval.op_val) = GE; lastValidTokenLine = tokenLineNum; }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 484 "fast_lang.y"
    { (yyval.op_val) = EQ; lastValidTokenLine = tokenLineNum; }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 485 "fast_lang.y"
    { (yyval.op_val) = NE; lastValidTokenLine = tokenLineNum; }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 488 "fast_lang.y"
    {
    if (exprType != "int") {
        string error = "Error: Arithmetic operation requires int operands, got " + (exprType.empty() ? "unknown" : exprType);
        yyerror(error.c_str());
    }
    string temp = newTemp();
    char op = (char)(yyvsp[(2) - (3)].op_val);
    threeAddressCode.push_back(temp + " := " + string((yyvsp[(1) - (3)].expr_val)) + " " + op + " " + string((yyvsp[(3) - (3)].expr_val)));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "int";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 500 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 505 "fast_lang.y"
    { (yyval.op_val) = '+'; lastValidTokenLine = tokenLineNum; }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 506 "fast_lang.y"
    { (yyval.op_val) = '-'; lastValidTokenLine = tokenLineNum; }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 509 "fast_lang.y"
    {
    if (exprType != "int") {
        string error = "Error: Arithmetic operation requires int operands, got " + (exprType.empty() ? "unknown" : exprType);
        yyerror(error.c_str());
    }
    string temp = newTemp();
    char op = (char)(yyvsp[(2) - (3)].op_val);
    threeAddressCode.push_back(temp + " := " + string((yyvsp[(1) - (3)].expr_val)) + " " + op + " " + string((yyvsp[(3) - (3)].expr_val)));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "int";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 521 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 526 "fast_lang.y"
    { (yyval.op_val) = '*'; lastValidTokenLine = tokenLineNum; }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 527 "fast_lang.y"
    { (yyval.op_val) = '/'; lastValidTokenLine = tokenLineNum; }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 528 "fast_lang.y"
    { (yyval.op_val) = '%'; lastValidTokenLine = tokenLineNum; }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 531 "fast_lang.y"
    {
    if (exprType != "int") {
        string error = "Error: Unary minus requires int operand, got " + (exprType.empty() ? "unknown" : exprType);
        yyerror(error.c_str());
    }
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := -" + string((yyvsp[(2) - (2)].expr_val)));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "int";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 542 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 547 "fast_lang.y"
    {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := " + to_string((yyvsp[(1) - (1)].int_val)));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "int";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 554 "fast_lang.y"
    {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := " + ((yyvsp[(1) - (1)].bool_val) ? "true" : "false"));
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "bool";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 561 "fast_lang.y"
    {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := \"" + string((yyvsp[(1) - (1)].str_val)) + "\"");
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "string";
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(1) - (1)].str_val));
}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 569 "fast_lang.y"
    {
    string temp = newTemp();
    threeAddressCode.push_back(temp + " := '" + string(1, (yyvsp[(1) - (1)].char_val)) + "'");
    (yyval.expr_val) = _strdup(temp.c_str());
    exprType = "char";
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 576 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 579 "fast_lang.y"
    {
    auto symbol = findSymbol((yyvsp[(1) - (1)].id));
    if (!symbol) {
        string error = "Error: Variable " + string((yyvsp[(1) - (1)].id)) + " used before declaration";
        yyerror(error.c_str());
        exprType = "unknown";
    } else if (symbol->isFunction) {
        string error = "Error: " + string((yyvsp[(1) - (1)].id)) + " is not a variable";
        yyerror(error.c_str());
        exprType = "unknown";
    } else {
        exprType = symbol->type.empty() ? "unknown" : symbol->type;
    }
    (yyval.expr_val) = _strdup((yyvsp[(1) - (1)].id));
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(1) - (1)].id));
}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 596 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(2) - (3)].expr_val);
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 602 "fast_lang.y"
    {
    parameterCount = 0;
    argumentTypes.clear();
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 606 "fast_lang.y"
    {
    auto symbol = findSymbol((yyvsp[(1) - (5)].id));
    if (!symbol) {
        string error = "Error: Function " + string((yyvsp[(1) - (5)].id)) + " used before declaration";
        yyerror(error.c_str());
        exprType = "unknown";
    } else if (!symbol->isFunction) {
        string error = "Error: " + string((yyvsp[(1) - (5)].id)) + " is not a function";
        yyerror(error.c_str());
        exprType = "unknown";
    } else if (symbol->paramTypes.size() != parameterCount) {
        string error = "Error: Function " + string((yyvsp[(1) - (5)].id)) + " expects " +
                       to_string(symbol->paramTypes.size()) + " arguments, got " +
                       to_string(parameterCount);
        yyerror(error.c_str());
        exprType = "unknown";
    } else {
        for (size_t i = 0; i < parameterCount; ++i) {
            if (!argumentTypes[i].empty() && argumentTypes[i] != symbol->paramTypes[i]) {
                string error = "Error: Type mismatch: argument " + to_string(i + 1) +
                               " of " + string((yyvsp[(1) - (5)].id)) + " expects " + symbol->paramTypes[i] +
                               ", got " + (argumentTypes[i].empty() ? "unknown" : argumentTypes[i]);
                yyerror(error.c_str());
            }
        }
        exprType = symbol->type.empty() ? "unknown" : symbol->type;
    }
    threeAddressCode.push_back("call " + string((yyvsp[(1) - (5)].id)) + ", " + to_string(parameterCount));
    string temp;
    if (symbol && symbol->type != "void") {
        temp = newTemp();
        threeAddressCode.push_back(temp + " := return_value");
    }
    (yyval.expr_val) = _strdup(temp.c_str());
    lastValidTokenLine = tokenLineNum;
    free((yyvsp[(1) - (5)].id));
}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 645 "fast_lang.y"
    {
    (yyval.expr_val) = (yyvsp[(1) - (1)].expr_val);
}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 648 "fast_lang.y"
    {
    (yyval.expr_val) = _strdup("");
}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 653 "fast_lang.y"
    {
    threeAddressCode.push_back("param " + string((yyvsp[(3) - (3)].expr_val)));
    argumentTypes.push_back(exprType.empty() ? "unknown" : exprType);
    parameterCount++;
    (yyval.expr_val) = _strdup(""); // Just a placeholder
    lastValidTokenLine = tokenLineNum;
}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 660 "fast_lang.y"
    {
    threeAddressCode.push_back("param " + string((yyvsp[(1) - (1)].expr_val)));
    argumentTypes.push_back(exprType.empty() ? "unknown" : exprType);
    parameterCount = 1;
    (yyval.expr_val) = _strdup(""); // Just a placeholder
    lastValidTokenLine = tokenLineNum;
}
    break;


/* Line 1792 of yacc.c  */
#line 2391 "fast_lang.tab.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 669 "fast_lang.y"


void yyerror(const char* s) {
    cerr << "Error at line " << lastValidTokenLine << ": " << s << endl;
}