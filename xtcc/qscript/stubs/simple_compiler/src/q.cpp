/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 8 "src/q.ypp"


//#include "common.h"

#include <inttypes.h>
#include <sys/types.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

//#include "tree.h"
#include "debug_mem.h"
#include "symtab.h"
#include "scope.h"
#include "expr.h"
#include "stmt.h"
#include "named_attributes.h"
#include "named_range.h"
#include "question.h"
#include "QuestionAttributes.h"

#include "qscript_parser.h"

	//using qscript_parser::yyerror;
	//using qscript_parser::yylex;
	//using qscript_parser::yywrap;
	extern int32_t yylex();
	extern void yyerror(const char * s);
	using std::cout;
	using std::cerr;
	using std::endl;
	int32_t flag_cmpd_stmt_is_a_func_body=-1;
	vector </*Statement::*/FunctionInformation*> func_info_table;
	QuestionAttributes question_attributes;
	map <string, int> map_duplicate_stub_entry_check;
	set< int> set_duplicate_stub_entry_check;
	vector <std::string> name_list;
	vector <std::string> recode_list;
	vector <std::string> driver_list;
	vector<TextExpression*> text_expr_vec;
	vector<string> vec_named_attribute_list;
	



/* Line 268 of yacc.c  */
#line 121 "src/q.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INUMBER = 258,
     FNUMBER = 259,
     NAME = 260,
     TOSTRING = 261,
     TEXT = 262,
     SINGLE_CODED = 263,
     MP = 264,
     VOID_T = 265,
     INT8_T = 266,
     INT16_T = 267,
     INT32_T = 268,
     FLOAT_T = 269,
     DOUBLE_T = 270,
     STRING_T = 271,
     IN = 272,
     FOR = 273,
     GOTO = 274,
     HIDDEN = 275,
     ALLOW_BLANK = 276,
     MUTEX = 277,
     CLEAR = 278,
     COLUMN = 279,
     ISANSWERED = 280,
     NEWCARD = 281,
     FIX = 282,
     BRAND_RANK = 283,
     DRIVERS = 284,
     CREATE_1_0_EDIT = 285,
     PAGE = 286,
     GRID_SIZE = 287,
     RANDOMIZE = 288,
     CONST = 289,
     LOGOR = 290,
     LOGAND = 291,
     NOEQ = 292,
     ISEQ = 293,
     GEQ = 294,
     LEQ = 295,
     NOT = 296,
     UMINUS = 297,
     COUNT = 298,
     FUNC_CALL = 299,
     IF = 300,
     ELSE = 301,
     STUBS_LIST = 302,
     NAMED_ATTRIBUTES = 303,
     SETDEL = 304,
     SETADD = 305,
     UNSET = 306,
     SETALL = 307
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 58 "src/q.ypp"

	type_qualifier type_qual;
	int32_t ival;
	double dval;
	char name[MY_STR_MAX];
	char text_buf[MY_STR_MAX];
	DataType dt;
	struct AbstractStatement * stmt;
	struct AbstractExpression * expr;
	//class AbstractQuestion* ques;
	struct CompoundStatement * c_stmt;
	struct FunctionParameter * v_list;





/* Line 293 of yacc.c  */
#line 227 "src/q.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 239 "src/q.cpp"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   854

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNRULES -- Number of states.  */
#define YYNSTATES  358

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    53,    66,     2,
      36,    37,    51,    50,    40,    49,    69,    52,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    71,    67,
      45,    38,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    70,     2,    68,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    39,
      41,    42,    43,    44,    47,    48,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    17,    19,    23,    26,
      32,    36,    37,    39,    42,    44,    46,    48,    50,    52,
      54,    56,    58,    62,    69,    75,    82,    84,    86,    88,
      90,    92,    94,    96,    98,   100,   102,   104,   106,   108,
     110,   112,   114,   116,   119,   120,   131,   135,   140,   142,
     148,   156,   159,   163,   169,   178,   189,   197,   203,   209,
     217,   226,   234,   236,   240,   242,   247,   254,   265,   267,
     268,   271,   273,   276,   278,   280,   284,   288,   292,   296,
     300,   303,   307,   311,   315,   319,   323,   327,   331,   335,
     339,   342,   344,   346,   348,   353,   358,   360,   364,   368,
     373,   377,   384,   389,   394,   396,   400,   402,   407,   412,
     414,   418,   422,   424,   428,   430,   434,   438,   440,   441,
     448,   454,   456,   460,   462,   465,   468,   472,   480,   491,
     501,   515,   528,   536,   547,   558,   566,   574,   580,   586,
     587,   596,   597,   604,   606,   609
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      73,     0,    -1,     5,    85,    -1,    74,    -1,    -1,    79,
       5,    36,    76,    37,    75,    85,    -1,    77,    -1,    76,
      40,    77,    -1,    79,     5,    -1,    79,     5,    34,     3,
      35,    -1,    79,    66,     5,    -1,    -1,    82,    -1,    78,
      82,    -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,
      14,    -1,    15,    -1,    16,    -1,    39,    -1,    79,     5,
      67,    -1,    80,    79,     5,    38,   100,    67,    -1,    79,
       5,    38,   100,    67,    -1,    79,     5,    34,   100,    35,
      67,    -1,    94,    -1,    89,    -1,    81,    -1,   108,    -1,
     110,    -1,    85,    -1,    88,    -1,    83,    -1,   114,    -1,
      90,    -1,    91,    -1,    92,    -1,   117,    -1,   120,    -1,
     115,    -1,    93,    -1,    86,    -1,     1,    67,    -1,    -1,
      18,    36,   100,    67,   100,    67,   100,    37,    84,    85,
      -1,    87,    78,    68,    -1,     5,    69,    33,    67,    -1,
      70,    -1,    58,    36,   100,    37,    82,    -1,    58,    36,
     100,    37,    82,    59,    82,    -1,   100,    67,    -1,    19,
       5,    67,    -1,    23,    36,     5,    37,    67,    -1,    23,
      36,     5,    34,   100,    35,    37,    67,    -1,    23,    36,
       5,    34,   100,    35,    40,     7,    37,    67,    -1,    23,
      36,     5,    40,     7,    37,    67,    -1,    24,    36,   100,
      37,    67,    -1,    26,    36,   100,    37,    67,    -1,     5,
      95,   102,    79,   105,    97,    67,    -1,     5,    95,   102,
      79,   105,   103,    97,    67,    -1,     5,    95,   102,    79,
       5,    97,    67,    -1,    96,    -1,    95,    71,    96,    -1,
       7,    -1,     5,    34,   100,    35,    -1,     5,    69,    60,
      34,   100,    35,    -1,    71,     5,    34,   100,    35,    69,
      60,    34,   100,    35,    -1,     5,    -1,    -1,    71,    98,
      -1,    99,    -1,    98,    99,    -1,    20,    -1,    21,    -1,
     100,    50,   100,    -1,   100,    49,   100,    -1,   100,    51,
     100,    -1,   100,    52,   100,    -1,   100,    53,   100,    -1,
      49,   100,    -1,   100,    45,   100,    -1,   100,    46,   100,
      -1,   100,    48,   100,    -1,   100,    47,   100,    -1,   100,
      44,   100,    -1,   100,    43,   100,    -1,   100,    41,   100,
      -1,   100,    42,   100,    -1,   100,    38,   100,    -1,    54,
     100,    -1,     3,    -1,     4,    -1,     5,    -1,     5,    34,
     100,    35,    -1,     5,    36,   101,    37,    -1,     7,    -1,
      36,   100,    37,    -1,   100,    17,   105,    -1,     6,    36,
       5,    37,    -1,   100,    17,     5,    -1,   100,    17,     5,
      34,   100,    35,    -1,    25,    36,     5,    37,    -1,    56,
      36,     5,    37,    -1,   100,    -1,   101,    40,   100,    -1,
       8,    -1,     9,    36,     3,    37,    -1,    22,    36,   104,
      37,    -1,   103,    -1,   104,    40,   103,    -1,     3,    49,
       3,    -1,     3,    -1,    36,   106,    37,    -1,   107,    -1,
     106,    40,   107,    -1,     3,    49,     3,    -1,     3,    -1,
      -1,    60,     5,   109,    38,   112,    67,    -1,    61,     5,
      38,   111,    67,    -1,     7,    -1,   111,    40,     7,    -1,
     113,    -1,   112,   113,    -1,     7,     3,    -1,     7,     3,
      22,    -1,    62,    36,     5,    40,     5,    37,    67,    -1,
      62,    36,     5,    40,     5,    34,   100,    35,    37,    67,
      -1,    63,    36,     5,    40,    36,     5,    37,    37,    67,
      -1,    63,    36,     5,    34,   100,    35,    40,     5,    34,
     100,    35,    37,    67,    -1,    63,    36,     5,    34,   100,
      35,    40,    36,     5,    37,    37,    67,    -1,    63,    36,
       5,    40,     5,    37,    67,    -1,    63,    36,     5,    40,
       5,    34,   100,    35,    37,    67,    -1,    63,    36,     5,
      34,   100,    35,    40,   105,    37,    67,    -1,    63,    36,
       5,    40,   105,    37,    67,    -1,    62,    36,     5,    40,
     105,    37,    67,    -1,    64,    36,     5,    37,    67,    -1,
      65,    36,     5,    37,    67,    -1,    -1,    28,   119,   116,
      29,   119,    71,     3,    67,    -1,    -1,    27,   119,   118,
      29,   119,    67,    -1,     5,    -1,   119,     5,    -1,    30,
       5,    67,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   175,   175,   183,   189,   189,   224,   228,   234,   241,
     250,   259,   267,   276,   284,   285,   286,   287,   288,   289,
     290,   293,   298,   301,   303,   306,   316,   317,   318,   319,
     320,   321,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   355,   355,   375,   381,   409,   419,
     438,   479,   500,   507,   513,   519,   524,   532,   539,   547,
     561,   574,   586,   587,   590,   593,   612,   635,   658,   682,
     683,   687,   688,   691,   694,   700,   709,   718,   727,   736,
     745,   754,   763,   772,   781,   790,   799,   808,   817,   826,
     835,   844,   853,   861,   869,   877,   931,   938,   945,   954,
     960,   966,   972,   978,   996,   997,  1002,  1008,  1013,  1018,
    1019,  1023,  1034,  1040,  1044,  1045,  1048,  1060,  1066,  1066,
    1112,  1126,  1129,  1136,  1137,  1140,  1170,  1204,  1208,  1234,
    1240,  1246,  1260,  1264,  1269,  1275,  1281,  1288,  1291,  1296,
    1296,  1320,  1320,  1343,  1344,  1348
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INUMBER", "FNUMBER", "NAME", "TOSTRING",
  "TEXT", "SINGLE_CODED", "MP", "VOID_T", "INT8_T", "INT16_T", "INT32_T",
  "FLOAT_T", "DOUBLE_T", "STRING_T", "IN", "FOR", "GOTO", "HIDDEN",
  "ALLOW_BLANK", "MUTEX", "CLEAR", "COLUMN", "ISANSWERED", "NEWCARD",
  "FIX", "BRAND_RANK", "DRIVERS", "CREATE_1_0_EDIT", "PAGE", "GRID_SIZE",
  "RANDOMIZE", "'['", "']'", "'('", "')'", "'='", "CONST", "','", "LOGOR",
  "LOGAND", "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'", "'+'",
  "'*'", "'/'", "'%'", "NOT", "UMINUS", "COUNT", "FUNC_CALL", "IF", "ELSE",
  "STUBS_LIST", "NAMED_ATTRIBUTES", "SETDEL", "SETADD", "UNSET", "SETALL",
  "'&'", "';'", "'}'", "'.'", "'{'", "':'", "$accept", "prog", "func_defn",
  "$@1", "decl_comma_list", "var_decl", "stmt_list", "datatype",
  "type_qual", "decl_stmt", "stmt", "for_loop_stmt", "$@2", "cmpd_stmt",
  "randomize_stmt", "open_curly", "if_stmt", "expr_stmt", "goto_stmt",
  "clear_stmt", "column_stmt", "newcard_stmt", "question",
  "text_expr_list", "text_expr", "attribute_list", "attributes",
  "attribute", "expression", "expr_list", "qtype", "mutex_range",
  "mutex_range_list", "range_allowed_values", "range_list", "range",
  "stubs", "$@3", "named_attributes", "named_attribute_list", "stub_list",
  "stub", "stub_manip_stmts", "brand_rank_recode_stmt", "$@4",
  "fix_and_recode_stmt", "$@5", "name_list", "create_1_0_data_edit_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,    91,    93,    40,    41,    61,   289,
      44,   290,   291,   292,   293,    60,    62,   294,   295,    45,
      43,    42,    47,    37,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,    38,    59,   125,    46,
     123,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    72,    73,    73,    75,    74,    76,    76,    77,    77,
      77,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      79,    80,    81,    81,    81,    81,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    84,    83,    85,    86,    87,    88,
      88,    89,    90,    91,    91,    91,    91,    92,    93,    94,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    97,
      97,    98,    98,    99,    99,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   101,   101,   102,   102,   103,   104,
     104,   103,   103,   105,   106,   106,   107,   107,   109,   108,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   116,
     115,   118,   117,   119,   119,   120
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     7,     1,     3,     2,     5,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     6,     5,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     0,    10,     3,     4,     1,     5,
       7,     2,     3,     5,     8,    10,     7,     5,     5,     7,
       8,     7,     1,     3,     1,     4,     6,    10,     1,     0,
       2,     1,     2,     1,     1,     3,     3,     3,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     4,     4,     1,     3,     3,     4,
       3,     6,     4,     4,     1,     3,     1,     4,     4,     1,
       3,     3,     1,     3,     1,     3,     3,     1,     0,     6,
       5,     1,     3,     1,     2,     2,     3,     7,    10,     9,
      13,    12,     7,    10,    10,     7,     7,     5,     5,     0,
       8,     0,     6,     1,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    15,    16,    17,    18,    19,    20,     0,
       3,     0,    48,     2,     0,     1,     0,     0,    91,    92,
      93,     0,    96,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    12,    33,
      31,    42,    32,    27,    35,    36,    37,    41,    26,     0,
      29,    30,    34,    40,    38,    39,    11,    43,    68,    64,
       0,     0,     0,     0,     0,    62,     0,     0,     0,     0,
       0,     0,     0,   143,   141,   139,     0,    93,     0,    80,
      90,     0,     0,   118,     0,     0,     0,     0,     0,    46,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       6,     0,     0,     0,     0,   104,     0,     0,     0,   106,
       0,     0,     0,     0,     0,    52,     0,     0,     0,     0,
     144,     0,     0,   145,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,     0,   100,     0,    98,
      89,    87,    88,    86,    85,    81,    82,    84,    83,    76,
      75,    77,    78,    79,     4,    11,     8,     0,     0,     0,
      94,    95,     0,    47,     0,     0,    63,     0,    99,     0,
       0,     0,     0,     0,   102,     0,     0,     0,   103,     0,
       0,   121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,   114,     0,     7,     0,    10,    65,
       0,   105,     0,     0,    69,    69,     0,     0,    53,     0,
      57,    58,     0,     0,    49,     0,     0,   123,     0,   120,
       0,     0,     0,     0,     0,     0,   137,   138,     0,    24,
       0,     0,     0,   113,     0,     5,     0,     0,     0,   107,
       0,     0,   112,     0,     0,    69,     0,     0,     0,   142,
       0,     0,   125,   119,   124,   122,     0,     0,     0,     0,
       0,     0,     0,     0,    25,    23,   101,   116,   115,     9,
      66,     0,    73,    74,    70,    71,    61,     0,     0,    59,
       0,     0,     0,     0,    56,     0,    50,   126,     0,   127,
     136,     0,     0,   132,     0,   135,     0,    72,   111,   109,
       0,    60,    44,    54,     0,   140,     0,     0,     0,     0,
       0,     0,     0,   108,     0,     0,     0,     0,     0,     0,
       0,     0,   129,     0,   110,    45,    55,   128,     0,     0,
     134,   133,    67,     0,     0,     0,   131,   130
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,   215,   119,   120,    44,    45,    46,    47,
      48,    49,   335,    50,    51,    14,    52,    53,    54,    55,
      56,    57,    58,    74,    75,   261,   294,   295,    59,   126,
     132,   265,   320,   159,   213,   214,    60,   147,    61,   202,
     236,   237,    62,    63,   142,    64,   141,    84,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -281
static const yytype_int16 yypact[] =
{
     105,   -48,  -281,  -281,  -281,  -281,  -281,  -281,  -281,    43,
    -281,    53,  -281,  -281,   260,  -281,    33,    -8,  -281,  -281,
      19,    77,  -281,   139,   102,   146,   147,   164,   165,   123,
     123,   171,     8,  -281,     8,     8,   176,   177,   218,   220,
     190,   191,   194,   196,   192,   228,   339,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,   294,
    -281,  -281,  -281,  -281,  -281,  -281,   339,  -281,    55,  -281,
       8,     8,   201,   231,     0,  -281,   232,     8,   172,   233,
       8,   235,     8,  -281,   237,   237,   180,     1,   479,   226,
     226,   239,     8,  -281,   213,   253,   254,   263,   264,  -281,
    -281,   -17,   272,    27,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,  -281,    71,
    -281,    29,     8,   221,   498,   801,    72,   215,   246,  -281,
     255,    22,   339,   252,   331,  -281,    92,   517,   256,   535,
    -281,   265,   266,  -281,  -281,   261,   554,   259,   285,   262,
       2,   267,   268,     8,     8,  -281,   270,   269,   297,  -281,
     801,    97,   117,    51,    51,   135,   135,   135,   135,    14,
      14,   226,   226,   226,  -281,   339,   276,   301,   573,   278,
    -281,  -281,     8,  -281,     8,   310,  -281,   100,  -281,     8,
       8,   248,   312,   250,  -281,   289,   123,   123,  -281,   260,
     319,  -281,   -20,   101,     8,   120,   290,   291,   592,   368,
       8,     8,   279,    90,  -281,   -48,  -281,   324,  -281,  -281,
       8,   801,   611,   292,   288,    16,   405,   630,  -281,   296,
    -281,  -281,    25,    23,   303,   328,     3,  -281,   353,  -281,
      11,   326,   649,   140,   130,   327,  -281,  -281,   298,  -281,
     442,   668,   363,  -281,   297,  -281,   332,   687,   299,  -281,
     134,   304,   321,   350,   320,   288,     8,   154,   322,  -281,
     385,   260,   369,  -281,  -281,  -281,     8,   323,   325,   354,
       8,   329,   356,   330,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,   335,  -281,  -281,   134,  -281,  -281,   396,    38,  -281,
     333,   706,   334,   395,  -281,   336,  -281,  -281,   725,  -281,
    -281,   173,   744,  -281,   367,  -281,   371,  -281,  -281,  -281,
     184,  -281,  -281,  -281,   370,  -281,   386,   374,   187,   387,
     388,   359,     8,  -281,    38,   -48,   360,   361,     8,   392,
     364,   365,  -281,   763,  -281,  -281,  -281,  -281,   782,   393,
    -281,  -281,  -281,   397,   366,   372,  -281,  -281
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -281,  -281,  -281,  -281,  -281,   286,  -281,     6,  -281,  -281,
     -42,  -281,  -281,    -1,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,   305,  -209,  -281,   143,   -31,  -281,
    -281,  -280,  -281,  -180,  -281,   186,  -281,  -281,  -281,  -281,
    -281,   202,  -281,  -281,  -281,  -281,  -281,   -25,  -281
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      13,    88,   100,    89,    90,    85,    11,   225,   129,   130,
     235,    18,    19,    87,    21,    22,   264,   153,   319,   262,
     238,   154,    12,   241,    68,   245,    69,    68,   140,    69,
     140,   103,   157,    27,   176,    70,   204,    71,   263,   124,
     125,   262,   205,    15,    32,   276,   134,   239,   277,   137,
     155,   139,   102,    70,   344,    71,   300,    34,    16,    67,
     263,   146,    35,   158,    36,   115,   116,   117,   103,    66,
     273,   131,   121,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   260,    72,   122,
      73,   178,   269,    73,   270,   177,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   224,   240,    78,   174,   181,
       1,   175,   182,    76,   103,     2,     3,     4,     5,     6,
       7,     8,   208,   209,   123,   243,   190,   253,    83,   191,
     254,   329,   192,   212,   103,   282,   158,   158,   187,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   221,   103,   222,   292,   293,   244,   234,   226,   227,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   232,   233,   242,   280,    77,    86,   281,   327,   250,
     251,   121,    79,    80,   113,   114,   115,   116,   117,   257,
     212,   302,   339,    17,   303,    18,    19,    20,    21,    22,
      81,    82,     2,     3,     4,     5,     6,     7,     8,   328,
      23,    24,    91,    92,   255,    25,    26,    27,    28,    29,
      30,   333,    31,    93,   334,    94,    95,    96,    32,   306,
      97,    33,    98,   101,   127,   301,   128,   133,   136,   135,
     138,    34,   140,   103,   145,   308,    35,   143,    36,   312,
      37,   148,    38,    39,    40,    41,    42,    43,   149,   150,
      99,    17,    12,    18,    19,    20,    21,    22,   151,   152,
       2,     3,     4,     5,     6,     7,     8,   156,    23,    24,
     184,   179,   183,    25,    26,    27,    28,    29,    30,   188,
      31,   185,   201,   194,   196,   197,    32,   200,   198,    33,
     212,   343,   203,   211,   206,   207,   218,   348,   210,    34,
     217,   103,   220,   223,    35,   228,    36,   230,    37,   229,
      38,    39,    40,    41,    42,    43,   235,   256,   252,   259,
      12,   272,   104,   268,   345,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   103,     2,
       3,     4,     5,     6,     7,     8,   231,   246,   247,   260,
     275,   118,   271,   278,   283,   284,   287,   289,   291,   104,
     297,   296,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   103,   298,   299,   305,   304,
     309,   307,   310,   314,   311,   316,   313,   315,   189,   318,
     321,   323,   324,   325,   331,   332,   104,   336,   338,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   103,   337,   340,   341,   342,   346,   347,   349,
     354,   350,   351,   356,   355,   249,   186,   317,   274,   357,
     288,     0,     0,   104,     0,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   103,
       0,   216,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   266,     0,     0,     0,     0,     0,     0,     0,
     104,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   285,
       0,     0,     0,     0,     0,   103,   144,   104,     0,     0,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   180,   103,     0,   104,     0,     0,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   103,     0,   193,   104,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   103,   195,   104,     0,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,     0,
     103,   199,   104,     0,     0,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   219,   103,
       0,   104,     0,     0,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   248,   103,     0,
     104,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   258,   103,     0,   104,
       0,     0,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   267,   103,     0,   104,     0,
       0,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   279,   103,     0,   104,     0,     0,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   286,   103,     0,   104,     0,     0,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   290,   103,     0,   104,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,     0,   103,   322,   104,     0,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     326,   103,     0,   104,     0,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   330,
     103,     0,   104,     0,     0,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   352,   103,
       0,   104,     0,     0,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   353,   103,     0,
     104,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,   104,
       0,     0,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-281))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    32,    44,    34,    35,    30,     0,   187,     8,     9,
       7,     3,     4,     5,     6,     7,   225,    34,   298,     3,
      40,    38,    70,   203,     5,   205,     7,     5,     5,     7,
       5,    17,     5,    25,     5,    34,    34,    36,    22,    70,
      71,     3,    40,     0,    36,    34,    77,    67,    37,    80,
      67,    82,    46,    34,   334,    36,   265,    49,     5,    67,
      22,    92,    54,    36,    56,    51,    52,    53,    17,    36,
      67,    71,    66,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,    71,    69,    34,
      71,   122,    67,    71,    71,    66,    45,    46,    47,    48,
      49,    50,    51,    52,    53,     5,     5,     5,    37,    37,
       5,    40,    40,    36,    17,    10,    11,    12,    13,    14,
      15,    16,   153,   154,    69,     5,    34,    37,     5,    37,
      40,   311,    40,     3,    17,     5,    36,    36,   132,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,   182,    17,   184,    20,    21,    36,   199,   189,   190,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,   196,   197,   204,    34,    36,     5,    37,     5,   210,
     211,   175,    36,    36,    49,    50,    51,    52,    53,   220,
       3,    37,     5,     1,    40,     3,     4,     5,     6,     7,
      36,    36,    10,    11,    12,    13,    14,    15,    16,    36,
      18,    19,    36,    36,   215,    23,    24,    25,    26,    27,
      28,    37,    30,     5,    40,     5,    36,    36,    36,   271,
      36,    39,    36,     5,    33,   266,     5,     5,     5,    67,
       5,    49,     5,    17,     5,   276,    54,    67,    56,   280,
      58,    38,    60,    61,    62,    63,    64,    65,     5,     5,
      68,     1,    70,     3,     4,     5,     6,     7,     5,     5,
      10,    11,    12,    13,    14,    15,    16,     5,    18,    19,
      34,    60,    67,    23,    24,    25,    26,    27,    28,    37,
      30,    36,     7,    37,    29,    29,    36,    38,    37,    39,
       3,   332,    40,    34,    37,    37,     5,   338,    38,    49,
      34,    17,    34,     3,    54,    67,    56,    67,    58,     7,
      60,    61,    62,    63,    64,    65,     7,     3,    49,    37,
      70,     3,    38,    37,   335,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    17,    10,
      11,    12,    13,    14,    15,    16,    67,    67,    67,    71,
       7,    67,    59,    37,    37,    67,     3,    35,    69,    38,
      49,    67,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    17,    36,    67,     3,    67,
      67,    22,    67,    37,    40,    60,    67,    67,    67,     3,
      67,    67,     7,    67,    37,    34,    38,    37,    34,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    17,    37,    37,    37,    67,    67,    67,    37,
      37,    67,    67,    67,    37,    67,   131,   294,   236,    67,
     254,    -1,    -1,    38,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    17,
      -1,   175,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    17,    37,    38,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    35,    17,    -1,    38,    -1,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    17,    -1,    37,    38,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    17,    37,    38,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      17,    37,    38,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    35,    17,
      -1,    38,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    35,    17,    -1,
      38,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    35,    17,    -1,    38,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    35,    17,    -1,    38,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    35,    17,    -1,    38,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    35,    17,    -1,    38,    -1,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    35,    17,    -1,    38,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    -1,    17,    37,    38,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      35,    17,    -1,    38,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    35,
      17,    -1,    38,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    35,    17,
      -1,    38,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    35,    17,    -1,
      38,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    -1,    -1,    -1,    38,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    10,    11,    12,    13,    14,    15,    16,    73,
      74,    79,    70,    85,    87,     0,     5,     1,     3,     4,
       5,     6,     7,    18,    19,    23,    24,    25,    26,    27,
      28,    30,    36,    39,    49,    54,    56,    58,    60,    61,
      62,    63,    64,    65,    78,    79,    80,    81,    82,    83,
      85,    86,    88,    89,    90,    91,    92,    93,    94,   100,
     108,   110,   114,   115,   117,   120,    36,    67,     5,     7,
      34,    36,    69,    71,    95,    96,    36,    36,     5,    36,
      36,    36,    36,     5,   119,   119,     5,     5,   100,   100,
     100,    36,    36,     5,     5,    36,    36,    36,    36,    68,
      82,     5,    79,    17,    38,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    67,    76,
      77,    79,    34,    69,   100,   100,   101,    33,     5,     8,
       9,    71,   102,     5,   100,    67,     5,   100,     5,   100,
       5,   118,   116,    67,    37,     5,   100,   109,    38,     5,
       5,     5,     5,    34,    38,    67,     5,     5,    36,   105,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,    37,    40,     5,    66,   100,    60,
      35,    37,    40,    67,    34,    36,    96,    79,    37,    67,
      34,    37,    40,    37,    37,    37,    29,    29,    37,    37,
      38,     7,   111,    40,    34,    40,    37,    37,   100,   100,
      38,    34,     3,   106,   107,    75,    77,    34,     5,    35,
      34,   100,   100,     3,     5,   105,   100,   100,    67,     7,
      67,    67,   119,   119,    82,     7,   112,   113,    40,    67,
       5,   105,   100,     5,    36,   105,    67,    67,    35,    67,
     100,   100,    49,    37,    40,    85,     3,   100,    35,    37,
      71,    97,     3,    22,    97,   103,    67,    35,    37,    67,
      71,    59,     3,    67,   113,     7,    34,    37,    37,    35,
      34,    37,     5,    37,    67,    67,    35,     3,   107,    35,
      35,    69,    20,    21,    98,    99,    67,    49,    36,    67,
      97,   100,    37,    40,    67,     3,    82,    22,   100,    67,
      67,    40,   100,    67,    37,    67,    60,    99,     3,   103,
     104,    67,    37,    67,     7,    67,    35,     5,    36,   105,
      35,    37,    34,    37,    40,    84,    37,    37,    34,     5,
      37,    37,    67,   100,   103,    85,    67,    67,   100,    37,
      67,    67,    35,    35,    37,    37,    67,    67
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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


/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  *++yyvsp = yylval;

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

/* Line 1806 of yacc.c  */
#line 175 "src/q.ypp"
    {
		qscript_parser::project_name = (yyvsp[(1) - (2)].name);
		qscript_parser::tree_root=(yyvsp[(2) - (2)].c_stmt);
		while(qscript_parser::tree_root->prev_) {
			cerr << "This should never appear: climbing up the tree" << endl;
			qscript_parser::tree_root=qscript_parser::tree_root->prev_;
		}
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 183 "src/q.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 189 "src/q.ypp"
    {
		string func_name_index((yyvsp[(2) - (5)].name));
		flag_cmpd_stmt_is_a_func_body=lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			ostringstream err_mesg;
			err_mesg << "Function name : " << func_name_index <<  "not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index;
			print_err(compiler_sem_err
					, err_mesg.str().c_str(),
					qscript_parser::line_no, __LINE__, __FILE__  );
		}
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 200 "src/q.ypp"
    {
		using qscript_parser::flagIsAForBody_;
		using qscript_parser::nest_lev;
		struct /* Statement:: */ CompoundStatement* c_stmt= (yyvsp[(7) - (7)].c_stmt);
		if (c_stmt==0) {
			cerr << "INTERNAL COMPILER ERROR: c_stmt==0" << endl;
		} else {
			//cout << "funcBody_: is valid " << endl;
		}
		struct Scope *scope_=c_stmt->scope_;
		struct /*Statement::*/ FunctionParameter * v_list=qscript_parser::trav_chain((yyvsp[(4) - (7)].v_list));
		struct /*Statement::*/ AbstractStatement* funcBody_=(yyvsp[(7) - (7)].c_stmt);
		string search_for=(yyvsp[(2) - (7)].name);
		DataType returnType_=(yyvsp[(1) - (7)].dt);
		(yyval.stmt)=new /*Statement::*/ FunctionStatement(FUNC_DEFN, qscript_parser::line_no, nest_lev, flagIsAForBody_, scope_, v_list, funcBody_, search_for, returnType_);
		// Note that the declaration already has a parameter list
		// the constructor uses the parameter list - name and type to verify everything
		// but doesnt need the parameter list any more - so we should delete it
		// - took me a while to figure out this memory leak
		delete v_list;
		free((yyvsp[(2) - (7)].name));
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 224 "src/q.ypp"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 228 "src/q.ypp"
    {
		(yyval.v_list)=qscript_parser::link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 234 "src/q.ypp"
    {
		(yyval.v_list)=new FunctionParameter((yyvsp[(1) - (2)].dt), (yyvsp[(2) - (2)].name));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(2) - (2)].name));
	}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 241 "src/q.ypp"
    {
		/* Neil - I need to fix this */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (5)].dt)-INT8_TYPE));
		(yyval.v_list)=new FunctionParameter(dt, (yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].ival));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(2) - (5)].name));
	}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 250 "src/q.ypp"
    {
		DataType dt=DataType(INT8_REF_TYPE+((yyvsp[(1) - (3)].dt)-INT8_TYPE));
		(yyval.v_list)=new FunctionParameter(dt, (yyvsp[(3) - (3)].name));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.v_list), __LINE__, __FILE__, qscript_parser::line_no);
		}
		free((yyvsp[(3) - (3)].name));
	}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 259 "src/q.ypp"
    {
		(yyval.v_list)=0;
		}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 267 "src/q.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
		if(qscript_parser::flag_next_stmt_start_of_block){
			qscript_parser::blk_heads.push_back((yyvsp[(1) - (1)].stmt));
			qscript_parser::flag_next_stmt_start_of_block=false;
			qscript_parser::blk_start_flag.pop_back();
		}

	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 276 "src/q.ypp"
    {
		(yyvsp[(1) - (2)].stmt) -> next_ = (yyvsp[(2) - (2)].stmt);
		(yyvsp[(2) - (2)].stmt) -> prev_ = (yyvsp[(1) - (2)].stmt);
		(yyval.stmt) = (yyvsp[(2) - (2)].stmt);
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 293 "src/q.ypp"
    {
		   (yyval.type_qual) = CONST_QUAL;
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 298 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 301 "src/q.ypp"
    {
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 303 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 306 "src/q.ypp"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].expr)/*, line_no*/);
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 321 "src/q.ypp"
    {
		(yyval.stmt) = (yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 335 "src/q.ypp"
    {
		fprintf (stderr, "continuing parse with errors around line_no: %d\n", qscript_parser::line_no);
		std::stringstream err_msg;
		err_msg << "continuing parsing"
			<< " file: " << qscript_parser::lex_location.fileName_
			<< " with errors around"
			<< " line: " << qscript_parser::lex_location.lineNo_
			<< " column: " << qscript_parser::lex_location.columnNo_ << std::endl;
		print_err(compiler_syntax_err
			, err_msg.str()
			, qscript_parser::lex_location.lineNo_, __LINE__, __FILE__);
		yyerrok;
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ErrorStatement(qscript_parser::line_no, 
				nest_lev, flagIsAForBody_);
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 355 "src/q.ypp"
    {
		++qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.push_back ((yyvsp[(5) - (8)].expr));
	        qscript_parser::ParseSpecialCaseAndAttachMaxBounds ((yyvsp[(5) - (8)].expr));
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 359 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::flagIsAForBody_;
		using qscript_parser::nest_lev;
		(yyval.stmt) = new ForStatement(FOR_STMT, line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (10)].expr), (yyvsp[(5) - (10)].expr), (yyvsp[(7) - (10)].expr), (yyvsp[(10) - (10)].c_stmt));

		--qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.pop_back();
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 375 "src/q.ypp"
    {
		(yyval.c_stmt) = qscript_parser::ProcessCompoundStatement((yyvsp[(1) - (3)].c_stmt), (yyvsp[(2) - (3)].stmt));
	}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 381 "src/q.ypp"
    {
		string name ((yyvsp[(1) - (4)].name));
		map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);
		if (sym_it  == qscript_parser::active_scope->SymbolTable.end()) {
			std::stringstream err_mesg;
			err_mesg << "symbol: " << name << " not found in symbol table. It should be a named_attribute list";
			print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			SymbolTableEntry * se = sym_it->second;
			RandomizeStatement * rand_stmt = 0;
			if (se->type_ == NAMED_ATTRIBUTE_TYPE) {
				rand_stmt = new RandomizeStatement (RANDOMIZE_STMT, qscript_parser::line_no,
						qscript_parser::nest_lev,
						qscript_parser::flagIsAForBody_, se->namedAttributes_);
			} else {
				std::stringstream err_mesg;
				err_mesg << "symbol: " << name << " should be a named_attribute or a question";
				print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
				rand_stmt = new RandomizeStatement (ERROR_TYPE, qscript_parser::line_no,
						qscript_parser::nest_lev,
						qscript_parser::flagIsAForBody_,
						0);
			}
			(yyval.stmt) = rand_stmt;
		}
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 409 "src/q.ypp"
    {
		CompoundStatement * cmpdStmt = qscript_parser::ProcessOpenCurly();
		//qscript_parser::compound_body_stack.push_back(cmpdStmt);
		//cmpdStmt->nestedCompoundStatementStack_=qscript_parser::compound_body_stack;
		(yyval.c_stmt)=cmpdStmt;
	}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 419 "src/q.ypp"
    {
		using qscript_parser::flagIsAForBody_;
		using qscript_parser::nest_lev;
		using qscript_parser::if_line_no;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::XTCC_DEBUG_MEM_USAGE;
		CompoundStatement * cmpd_stmt = dynamic_cast<CompoundStatement*>((yyvsp[(5) - (5)].stmt));
		if (cmpd_stmt!=0) {
			cmpd_stmt->flagIsAIfBody_ = 1;
			IfStatement * if_stmt = new IfStatement (IFE_STMT, if_line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr), cmpd_stmt, 0);
			cmpd_stmt->ifStatement_ = if_stmt;
			(yyval.stmt) = if_stmt;
		} else 
			(yyval.stmt)=new IfStatement (IFE_STMT, if_line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt), 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 438 "src/q.ypp"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::flagIsAForBody_;
		using qscript_parser::nest_lev;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		CompoundStatement * cmpd_stmt_if_body = dynamic_cast<CompoundStatement*>((yyvsp[(5) - (7)].stmt));
		if (cmpd_stmt_if_body) {
			cmpd_stmt_if_body->flagIsAIfBody_ = 1;
		}
		CompoundStatement * cmpd_stmt_else_body = dynamic_cast<CompoundStatement*>((yyvsp[(7) - (7)].stmt));
		if (cmpd_stmt_else_body) {
			cmpd_stmt_else_body->flagIsAIfBody_ = 1;
		}

		IfStatement * if_else_stmt = 0;
		if (cmpd_stmt_if_body==0 && cmpd_stmt_else_body==0)
			if_else_stmt = new IfStatement (IFE_STMT, if_line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (7)].expr) , (yyvsp[(5) - (7)].stmt), (yyvsp[(7) - (7)].stmt));
		else if (cmpd_stmt_if_body != 0 && cmpd_stmt_else_body !=0 ) 
			if_else_stmt = new IfStatement (IFE_STMT, if_line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (7)].expr), cmpd_stmt_if_body, cmpd_stmt_else_body);
		else if (cmpd_stmt_else_body !=0 && cmpd_stmt_if_body==0) 
			if_else_stmt = new IfStatement (IFE_STMT, if_line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].stmt), cmpd_stmt_else_body);
		else 
			if_else_stmt = new IfStatement (IFE_STMT, if_line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (7)].expr), cmpd_stmt_if_body, (yyvsp[(7) - (7)].stmt));
		
		(yyval.stmt) = if_else_stmt;

		if (cmpd_stmt_if_body) {
			cmpd_stmt_if_body->ifStatement_ = if_else_stmt;
		}
		if (cmpd_stmt_else_body) {
			cmpd_stmt_else_body->ifStatement_ = if_else_stmt;
		}

		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.stmt), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 480 "src/q.ypp"
    {
		using qscript_parser::if_line_no;
		using qscript_parser::flagIsAForBody_;
		using qscript_parser::nest_lev;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		if((yyvsp[(1) - (2)].expr)->IsValid()){
			(yyval.stmt) = new ExpressionStatement(TEXPR_STMT, line_no, nest_lev, flagIsAForBody_, (yyvsp[(1) - (2)].expr));
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE) {
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		} else {
			(yyval.stmt) = new ExpressionStatement(ERROR_TYPE, line_no, nest_lev, flagIsAForBody_, (yyvsp[(1) - (2)].expr));
			if(qscript_parser::XTCC_DEBUG_MEM_USAGE) {
				mem_log((yyval.stmt), __LINE__, __FILE__, line_no);
			}
		}
	}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 500 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new GotoStatement(GOTO_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(2) - (3)].name));
		// free($2); ? is this required here
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 507 "src/q.ypp"
    {
		// free($3); ? is this required here
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].name));
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 513 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (8)].name), (yyvsp[(5) - (8)].expr));
		// free($3); ? is this required here
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 519 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (10)].name), (yyvsp[(5) - (10)].expr), (yyvsp[(8) - (10)].text_buf));
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 524 "src/q.ypp"
    {
		// free($3); ? is this required here
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (7)].name), (yyvsp[(5) - (7)].text_buf));
	}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 532 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ColumnStatement(COLUMN_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr));
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 539 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new NewCardStatement(COLUMN_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr));
	}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 547 "src/q.ypp"
    {
		// Warning : xs is a global variable that is used here
		//$$ = qscript_parser::ProcessRangeQuestion($1, $2, $4);
		(yyval.stmt) = qscript_parser::ProcessRangeQuestion((yyvsp[(1) - (7)].name), "dummy question text", (yyvsp[(4) - (7)].dt));
		//cout << "parsed range question : " << $1 << endl;
		question_attributes.Reset();
		using qscript_parser::xs;
		xs.reset();
		std::stringstream mesg;
		mesg << "fix memory leak problem introduced at this point";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		// huge memory leak 
		text_expr_vec.clear();
	}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 561 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::ProcessRangeQuestion((yyvsp[(1) - (8)].name), "dummy question text" , (yyvsp[(4) - (8)].dt));
		//cout << "parsed range question : " << $1 << endl;
		question_attributes.Reset();
		qscript_parser::has_mutex_range = false;
		using qscript_parser::xs;
		xs.reset();
		std::stringstream mesg;
		mesg << "fix memory leak problem introduced at this point";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		// huge memory leak 
		text_expr_vec.clear();
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 574 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::ProcessNamedQuestion((yyvsp[(1) - (7)].name), "dummy question text", (yyvsp[(4) - (7)].dt), (yyvsp[(5) - (7)].name));
		//cout << "parsed named question : " << $1 << endl;
		question_attributes.Reset();
		std::stringstream mesg;
		mesg << "fix memory leak problem introduced at this point";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		// huge memory leak 
		text_expr_vec.clear();
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 590 "src/q.ypp"
    {
		text_expr_vec.push_back (new TextExpression(string((yyvsp[(1) - (1)].text_buf))));
	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 593 "src/q.ypp"
    {
		string name ((yyvsp[(1) - (4)].name));
		map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);

		if ( sym_it  == qscript_parser::active_scope->SymbolTable.end() ){
			std::stringstream err_mesg;
			err_mesg << "symbol: " << name << " not found in symbol table. It should be a named_attribute list";
			print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			SymbolTableEntry * se = sym_it->second;
			if (se->type_ == NAMED_ATTRIBUTE_TYPE) {
				text_expr_vec.push_back (new TextExpression(new Unary2Expression (oper_arrderef, (yyvsp[(1) - (4)].name), (yyvsp[(3) - (4)].expr))));
			} else {
				std::stringstream err_mesg;
				err_mesg << "symbol: " << name << " should be a named_attribute or a question";
				print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			}
		}
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 612 "src/q.ypp"
    {

		string name ((yyvsp[(1) - (6)].name));
		map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);
		if ( sym_it  == qscript_parser::active_scope->SymbolTable.end() ){
			std::stringstream err_mesg;
			err_mesg << "symbol: " << name << " not found in symbol table. It should be a named_attribute list";
			print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			SymbolTableEntry * se = sym_it->second;
			if (se->type_ == QUESTION_TYPE) {
				text_expr_vec.push_back (new TextExpression(se->question_, 0, (yyvsp[(5) - (6)].expr)) );
				std::stringstream err_mesg;
				//err_mesg << "symbol: " << name << " question - unhandled case";
				//print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			} else {
				std::stringstream err_mesg;
				err_mesg << "symbol: " << name << " should be a named_attribute or a question";
				print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			}
		}

	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 635 "src/q.ypp"
    {

		string name ((yyvsp[(2) - (10)].name));
		map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);
		if ( sym_it  == qscript_parser::active_scope->SymbolTable.end() ){
			std::stringstream err_mesg;
			err_mesg << "symbol: " << name << " not found in symbol table. It should be a named_attribute list";
			print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			SymbolTableEntry * se = sym_it->second;
			if (se->type_ == QUESTION_ARR_TYPE) {
				text_expr_vec.push_back (new TextExpression(se->question_, (yyvsp[(4) - (10)].expr), (yyvsp[(9) - (10)].expr)) );
				std::stringstream err_mesg;
				//err_mesg << "symbol: " << name << " question - unhandled case";
				//print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			} else {
				std::stringstream err_mesg;
				err_mesg << "symbol: " << name << " should be a named_attribute or a array question ";
				print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			}
		}

	}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 658 "src/q.ypp"
    {

		string name ((yyvsp[(1) - (1)].name));
		map<string,SymbolTableEntry*>::iterator sym_it = find_in_symtab(name);
		if ( sym_it  == qscript_parser::active_scope->SymbolTable.end() ){
			std::stringstream err_mesg;
			err_mesg << "symbol: " << name << " not found in symbol table. It should be a named_attribute list";
			print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			SymbolTableEntry * se = sym_it->second;
			if (se->type_ == QUESTION_TYPE) {
				text_expr_vec.push_back (new TextExpression (se->question_));
				std::stringstream err_mesg;
				//err_mesg << "symbol: " << name << " question - unhandled case";
				//print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			} else {
				std::stringstream err_mesg;
				err_mesg << "symbol: " << name << " should be a named_attribute or a question";
				print_err(compiler_sem_err, err_mesg.str(), qscript_parser::line_no, __LINE__, __FILE__);
			}
		}
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 691 "src/q.ypp"
    {
		question_attributes.setHidden();
	}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 694 "src/q.ypp"
    {
		question_attributes.setAllowBlank();
	}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 700 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		using qscript_parser::mem_addr;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_plus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 709 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_minus);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 718 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mult);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 727 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_div);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 736 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_mod);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 745 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (2)].expr), oper_umin);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 754 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_lt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 763 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_gt);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 772 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_le);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 781 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_ge);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 790 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_iseq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 799 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_isneq);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 808 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_or);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 817 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr)=new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_and);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 826 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new BinaryExpression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), oper_assgn);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 835 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (2)].expr), oper_not);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 844 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].ival));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 853 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].dval));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 861 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].name), oper_name );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 869 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		(yyval.expr) = new Unary2Expression(oper_arrderef, (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 877 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::named_stubs_list;
		using qscript_parser::func_info_table;
		using qscript_parser::xs;
		using qscript_parser::q_type;
		using qscript_parser::no_mpn;
		using qscript_parser::trav_chain;
		using qscript_parser::skip_func_type_check;
		using qscript_parser::check_parameters;
		using qscript_parser::link_chain;
		using qscript_parser::stub_list;
		using qscript_parser::line_no;
		using qscript_parser::no_errors;
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=(yyvsp[(1) - (4)].name);
		bool found=false;
		int32_t index=search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: "
				<< line_no << endl;
			cerr << "function : " << search_for
				<< " used without decl" << endl;
			++ no_errors;
			(yyval.expr)=new Unary2Expression(ERROR_TYPE);
			void *ptr=(yyval.expr);
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else {
			DataType my_type=func_info_table[index]->returnType_;
			AbstractExpression* e_ptr=trav_chain((yyvsp[(3) - (4)].expr));
			FunctionParameter* fparam=
				func_info_table[index]->parameterList_;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new Unary2Expression(oper_func_call, my_type, $3, index, line_no);
				//$$=new Unary2Expression(oper_func_call, my_type, e_ptr, index, line_no);
				(yyval.expr)=new Unary2Expression(oper_func_call, my_type, e_ptr, index);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			} else {
				(yyval.expr)=new Unary2Expression(ERROR_TYPE);
				void *ptr=(yyval.expr);
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 931 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 938 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (3)].expr), oper_parexp );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 945 "src/q.ypp"
    {
		using qscript_parser::xs;
		using qscript_parser::line_no;
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (3)].expr), xs, oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
		xs.reset();
	}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 954 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression((yyvsp[(3) - (4)].name), oper_to_string);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 960 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].name), 0, oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 966 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (6)].expr), (yyvsp[(3) - (6)].name), (yyvsp[(5) - (6)].expr), oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 972 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_isanswered);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 978 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_count);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 996 "src/q.ypp"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 997 "src/q.ypp"
    {
		(yyval.expr)=qscript_parser::link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1002 "src/q.ypp"
    { 
	       qscript_parser::q_type = spn; 
	       // we need this =1 when generating
	       // code for flat file creation
		qscript_parser::no_mpn = 1;
       }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1008 "src/q.ypp"
    { qscript_parser::q_type = mpn;
		qscript_parser::no_mpn = (yyvsp[(3) - (4)].ival);
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1013 "src/q.ypp"
    { 
		     qscript_parser::has_mutex_range = true;
	     }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1023 "src/q.ypp"
    {
		using qscript_parser::line_no;
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(compiler_sem_err
					, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			qscript_parser:: mutex_range_set.add_range ( (yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival));
		}
	}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1034 "src/q.ypp"
    {
		qscript_parser::mutex_range_set.add_indiv((yyvsp[(1) - (1)].ival));
	}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1040 "src/q.ypp"
    { }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1048 "src/q.ypp"
    {
		using qscript_parser::line_no;
		if((yyvsp[(3) - (3)].ival)<=(yyvsp[(1) - (3)].ival)){
			print_err(compiler_sem_err
					, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			//qscript_parser:: xs.range.push_back( pair<int32_t,int32_t>($1,$3));
			qscript_parser:: xs.add_range ( (yyvsp[(1) - (3)].ival),(yyvsp[(3) - (3)].ival));
		}
	}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1060 "src/q.ypp"
    {
		//qscript_parser::xs.indiv.insert($1);
		qscript_parser::xs.add_indiv((yyvsp[(1) - (1)].ival));
	}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1066 "src/q.ypp"
    {
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		stub_list.resize(0);
                string name ((yyvsp[(2) - (2)].name));
                if (qscript_parser::active_scope_list[0]->find (name)) {
                        std::stringstream s;
                        s << "variable " << name << " already present in symbol table" << endl;
                        print_err (compiler_sem_err, s.str(), qscript_parser::line_no, __LINE__, __FILE__);
                }
                if (qscript_parser::named_stub_exists (name)) {
                        std::stringstream err_mesg;
                        err_mesg << "stub by this name already exist: "
                                << (yyvsp[(2) - (2)].name);
                        print_err (compiler_sem_err, 
                                err_mesg.str().c_str(),
                                qscript_parser::line_no, __LINE__,
                                        __FILE__);
                }
		map_duplicate_stub_entry_check.clear();
		set_duplicate_stub_entry_check.clear();
	}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1087 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=(yyvsp[(2) - (6)].name);

                std::stringstream mesg;
		// 14-mar-2013 - I think this has already been actioned
                //mesg << " put a check for duplicate name in stub list";
                //LOG_MAINTAINER_MESSAGE (mesg.str());
                mesg.str().clear();
                mesg << " make variables in for loop in quest_defns_init_code area unique by prepending qscript_";
                LOG_MAINTAINER_MESSAGE (mesg.str());
		struct named_range* nr_ptr= new named_range(NAMED_RANGE
				, line_no, stub_name,stub_list);
		named_stubs_list.push_back(nr_ptr);
		bool success = qscript_parser::verify_stubs_list (nr_ptr);
		//$$=0;
		(yyval.stmt) = nr_ptr;
	}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1112 "src/q.ypp"
    {
		//$$ = new named_attribute_list (NAMED_ATTRIBUTE_TYPE, $2, vec_named_attribute_list);
		//qscript_parser::delete_manually_in_cleanup.push_back(
		(yyval.stmt) = qscript_parser::active_scope_list[0]->insert(
				(yyvsp[(2) - (5)].name), NAMED_ATTRIBUTE_TYPE
				, qscript_parser::line_no 
				, qscript_parser::nest_lev
				, qscript_parser::flagIsAForBody_
				, vec_named_attribute_list);
		//);
		vec_named_attribute_list.clear();
	}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1126 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(1) - (1)].text_buf));
	}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1129 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(3) - (3)].text_buf));
	}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1140 "src/q.ypp"
    {
		using qscript_parser::stub_list;
		string s1=(yyvsp[(1) - (2)].text_buf);
		int32_t code=(yyvsp[(2) - (2)].ival);
		struct stub_pair pair1(s1,code);
		stub_list.push_back(pair1);

		map <string,int>::iterator map_iter = map_duplicate_stub_entry_check.find(s1);
		//cout << "searching for : " << s1 << " in map" << endl;
		if (map_iter != map_duplicate_stub_entry_check.end()) {
			std::stringstream err_msg;
			err_msg << "the stub text: \"" << s1
				<< "\" with code: " << code
				<< " already exists with a code value of : "
				<< map_iter->second;
			print_err(compiler_syntax_err, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			map_duplicate_stub_entry_check[s1] = code;
		}

		set<int>::iterator set_iter = set_duplicate_stub_entry_check.find (code);
		if (set_iter != set_duplicate_stub_entry_check.end()) {
			std::stringstream err_msg;
			err_msg << "the code: " << code
				<< " already exists in the stub list: ";
			print_err(compiler_syntax_err, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			set_duplicate_stub_entry_check.insert(code);
		}
	}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1170 "src/q.ypp"
    {
		using qscript_parser::stub_list;
		string s1=(yyvsp[(1) - (3)].text_buf);
		int32_t code=(yyvsp[(2) - (3)].ival);
		struct stub_pair pair1(s1,code, true);
		stub_list.push_back(pair1);
		//cout << "chaining stublist" << endl;
		
		map <string,int>::iterator map_iter = map_duplicate_stub_entry_check.find(s1);
		//cout << "searching for : " << s1 << " in map" << endl;
		if (map_iter != map_duplicate_stub_entry_check.end()) {
			std::stringstream err_msg;
			err_msg << "the stub text: \"" << s1
				<< "\" with code: " << code
				<< " already exists with a code value of : "
				<< map_iter->second;
			print_err(compiler_syntax_err, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			map_duplicate_stub_entry_check[s1] = code;
		}

		set<int>::iterator set_iter = set_duplicate_stub_entry_check.find (code);
		if (set_iter != set_duplicate_stub_entry_check.end()) {
			std::stringstream err_msg;
			err_msg << "the code: " << code
				<< " already exists in the stub list";
			print_err(compiler_syntax_err, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		} else {
			set_duplicate_stub_entry_check.insert(code);
		}
	}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1204 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), 0, (yyvsp[(5) - (7)].name), 0);
	}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1208 "src/q.ypp"
    {
		AbstractExpression * a_expr = (yyvsp[(7) - (10)].expr);
		Unary2Expression * arr_r_index
			= dynamic_cast<Unary2Expression*> (a_expr);
			
		//UnaryExpression * e1 = dynamic_cast<UnaryExpression*> (a_expr);
		//if (e1) {
		//	cout << " is UnaryExpression" << endl;
		//}
		//BinaryExpression * b1 = dynamic_cast<BinaryExpression*> (a_expr);
		//if (b1) {
		//	cout << " is BinaryExpression" << endl;
		//}
		if (arr_r_index) {
			(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (10)].name), 0, (yyvsp[(5) - (10)].name), (yyvsp[(7) - (10)].expr));
		} else {
			(yyval.stmt) = new ErrorStatement(qscript_parser::line_no,
				qscript_parser::nest_lev, qscript_parser::flagIsAForBody_);
			std::stringstream err_msg;
			err_msg << "array indexing expression should be integer expression";
			print_err(compiler_syntax_err
				, err_msg.str()
				, qscript_parser::lex_location.lineNo_, __LINE__, __FILE__);
		}
	}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1234 "src/q.ypp"
    {
                // 2nd NAME is an expression
                Unary2Expression * un2e = new Unary2Expression ((yyvsp[(6) - (9)].name), oper_name);
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (9)].name), 0, un2e);
	}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1240 "src/q.ypp"
    {
		cout << __LINE__ << "|^: reached here" << endl;		
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (13)].name), (yyvsp[(5) - (13)].expr), (yyvsp[(8) - (13)].name), (yyvsp[(10) - (13)].expr));
        }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1246 "src/q.ypp"
    {
                // 2nd NAME is an expression
                //Unary2Expression * arr_index = new Unary2Expression ($5, oper_name);
                Unary2Expression * arr_index = 
			dynamic_cast<Unary2Expression*> ((yyvsp[(5) - (12)].expr));
       		if (arr_index) { 
	                Unary2Expression * un2e = new Unary2Expression ((yyvsp[(9) - (12)].name), oper_name);
			(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (12)].name), arr_index, un2e);
		} else {
			(yyval.stmt) = new ErrorStatement(qscript_parser::line_no, 
				qscript_parser::nest_lev, qscript_parser::flagIsAForBody_);
		}
	}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1260 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), 0, (yyvsp[(5) - (7)].name), 0);
	}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1264 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), 0, (yyvsp[(5) - (10)].name), (yyvsp[(7) - (10)].expr));
		//cout << "reached here" << endl;		
	}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1269 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), (yyvsp[(5) - (10)].expr), xs);
		xs.reset();
        }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1275 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), 0, xs);
		xs.reset();
	}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1281 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), 0, xs);
		//using qscript_parser::xs;
		xs.reset();
	}
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1288 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_UNSET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1291 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_SET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1296 "src/q.ypp"
    { recode_list = name_list; name_list.clear(); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1297 "src/q.ypp"
    {
		driver_list = name_list ;
		using qscript_parser::line_no;
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
                /*
		if (recode_list.size() % driver_list.size() != 0) {
			ostringstream err_mesg;
			err_mesg << "No of variables in recode list should be exactly divisible by no of variables in driver_list ";
			print_err(compiler_sem_err,
					err_mesg.str().c_str(),
					qscript_parser::line_no, __LINE__, __FILE__);
		}
                */
		BrandRankRecodeStatement * brand_rank_recode_stmt = new BrandRankRecodeStatement (
			BRAND_RANK_STMT, line_no, nest_lev, flagIsAForBody_,
			recode_list, driver_list, (yyvsp[(7) - (8)].ival));
		recode_list.clear();
		driver_list.clear();
		qscript_parser::brand_rank_recode_driver_vec.push_back (brand_rank_recode_stmt);
		(yyval.stmt) = brand_rank_recode_stmt;
	}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1320 "src/q.ypp"
    { recode_list = name_list; name_list.clear(); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1321 "src/q.ypp"
    {
		driver_list = name_list ;
		using qscript_parser::line_no;
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		if (recode_list.size() % driver_list.size() != 0) {
			ostringstream err_mesg;
			err_mesg << "No of variables in recode list should be exactly divisible by no of variables in driver_list ";
			print_err(compiler_sem_err,
					err_mesg.str().c_str(),
					qscript_parser::line_no, __LINE__, __FILE__);
		}
		FixAndRecodeStatement * fix_and_recode_stmt = new FixAndRecodeStatement (
			FIX_AND_RECODE_STMT, line_no, nest_lev, flagIsAForBody_,
			recode_list, driver_list);
		recode_list.clear();
		driver_list.clear();
		qscript_parser::recode_driver_vec.push_back (fix_and_recode_stmt);
		(yyval.stmt) = fix_and_recode_stmt;
	}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1343 "src/q.ypp"
    { name_list.push_back((yyvsp[(1) - (1)].name)); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1344 "src/q.ypp"
    { name_list.push_back((yyvsp[(2) - (2)].name)); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1348 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		Create_1_0_DataEditStatement * create_1_0_data_edit = new Create_1_0_DataEditStatement(
			CREATE_1_0_EDIT_STMT, line_no, nest_lev, flagIsAForBody_, string((yyvsp[(2) - (3)].name))
			);
		qscript_parser::create_1_0_edit_vec.push_back (create_1_0_data_edit);
		(yyval.stmt) = create_1_0_data_edit;
	}
    break;



/* Line 1806 of yacc.c  */
#line 3561 "src/q.cpp"
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 2067 of yacc.c  */
#line 1361 "src/q.ypp"



#include "utils.h"
#include <unistd.h>
#include <string>

namespace qscript_parser {

template<class T> T* link_chain(T* &elem1, T* &elem2){
	if(elem1 && elem2){
		elem2->prev_=elem1;
		elem1->next_=elem2;
		return elem2;
	}
	else if(elem1){
		return elem1;
	} else {
		return elem2;
	}
}


template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev_) elem1=elem1->prev_;
		return elem1;
	} else return 0;
}

//! The array size of a question inside a for loop
//! is determined by the nesting level of the question inside the
//! for loop and the maximum bound of the loop index - it is a multiplication
//! of all the maximum counters in the enclosing for loops
AbstractExpression * recurse_for_index(int32_t stack_index){
	//cerr << "entered: recurse_for_index: stack_index: " << stack_index << endl;
	if(stack_index==0){
		BinaryExpression * test_expr =
			dynamic_cast<BinaryExpression*>(
					for_loop_max_counter_stack[0]);
		if(test_expr==0){
			print_err(compiler_sem_err,
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
			return 0;
		} else if(test_expr->rightOperand_->IsIntegralExpression()
				&& test_expr->rightOperand_->IsConst()) {
			return test_expr->rightOperand_;
		} else {
			print_err(compiler_sem_err,
				" test expr not integer and const",
				qscript_parser::line_no, __LINE__, __FILE__);
			return test_expr->rightOperand_;
		}
	} else {
		BinaryExpression * test_expr =
			dynamic_cast<BinaryExpression*>(
				for_loop_max_counter_stack[stack_index]);
		if(test_expr==0){
			print_err(compiler_sem_err,
				" test expr should be a binary expression ",
				qscript_parser::line_no, __LINE__, __FILE__);
			return 0;
		} else if(test_expr->rightOperand_->IsIntegralExpression()
				&& test_expr->rightOperand_->IsConst()) {
			return new BinaryExpression(test_expr->rightOperand_,
				recurse_for_index(stack_index-1), oper_mult);
		} else {
			print_err(compiler_sem_err,
				" test expr not integer and const",
				qscript_parser::line_no, __LINE__, __FILE__);
			return test_expr->rightOperand_;
		}
	}
}

CompoundStatement* ProcessOpenCurly()
{
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
	++nest_lev;
	CompoundStatement * cmpdStmt= new CompoundStatement(CMPD_STMT,
			line_no, nest_lev, flagIsAForBody_,
			flagIsAFunctionBody_,
			flagIsAForBody_, for_loop_max_counter_stack);
	stack_cmpd_stmt.push_back(cmpdStmt);
	cmpdStmt->nestedCompoundStatementStack_=stack_cmpd_stmt;
	void *ptr=cmpdStmt;
	mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
	mem_addr.push_back(m1);
	if(flagIsAFunctionBody_>=0){
		cmpdStmt->scope_=func_info_table[
			qscript_parser::flagIsAFunctionBody_]->functionScope_;
		// reset the flag
		qscript_parser::flagIsAFunctionBody_=-1;
	} else {
		cmpdStmt->scope_= new Scope();
	}
	flag_next_stmt_start_of_block=true;
	flag_next_question_start_of_block = true;
	blk_start_flag.push_back(flag_next_stmt_start_of_block);
	blk_question_start_flag.push_back(flag_next_question_start_of_block);
	active_scope_list.push_back(cmpdStmt->scope_);
	active_scope = cmpdStmt->scope_;
	return cmpdStmt;
}

CompoundStatement* ProcessCompoundStatement(CompoundStatement* cmpdStmt,
		AbstractStatement *stmt)
{

	active_scope_list.pop_back();
	int32_t tmp=active_scope_list.size()-1;
	if(tmp==-1) {
		active_scope = 0;
		print_err(compiler_internal_error
			, "Error: active_scope == 0 in ProcessCompoundStatement"
			": should never happen :... exiting",
				line_no, __LINE__, __FILE__  );
		exit(1);
	} else {
		active_scope = active_scope_list[tmp];
	}
	struct AbstractStatement* head_of_this_chain=blk_heads.back();
	if(blk_start_flag.size() > 0) {
		flag_next_stmt_start_of_block = blk_start_flag[blk_start_flag.size()-1];
	}
	if (blk_question_start_flag.size() > 0) {
		//flag_next_question_start_of_block = blk_question_start_flag[blk_question_start_flag.size()-1];
		blk_question_start_flag.pop_back();
		flag_next_question_start_of_block = blk_question_start_flag.back();
	}
	if (head_of_this_chain == 0) {
		//cerr << "Error in compiler : compoundBody_:  " << __FILE__ << __LINE__ << endl;
		//++no_errors;
		print_err(compiler_internal_error
			, "Error: head_of_this_chain == 0 in "
			  "ProcessCompoundStatement : should never happen :"
			  "... exiting"
			, line_no, __LINE__, __FILE__  );
		exit(1);
	} else {
		cmpdStmt->compoundBody_ = head_of_this_chain;
		blk_heads.pop_back();
	}

	//! update the counter of enlosing CompoundStatement with
	//! the number of questions in this CompoundStatement being popped of
	//! right now
	if(stack_cmpd_stmt.size()>1){
		CompoundStatement * popped_off_cmpd_stmt_ptr=stack_cmpd_stmt.back();
		stack_cmpd_stmt.pop_back();
		CompoundStatement * current  = stack_cmpd_stmt.back();
		current->counterContainsQuestions_+=
			(popped_off_cmpd_stmt_ptr->counterContainsQuestions_);
	}
	//$$=$1;
	return cmpdStmt;
}

// NxD: 10-Jun-2010
// Need to make changes here - create a new struct to store variable name and type
// and dump the entire scope into the map
// later the question::GenerateCode will
// decide by looking if it is an array question or a simple
// question and generate the appropriate save restore scope code
AbstractStatement * ProcessRangeQuestion(const string &name
		, const string & q_text, const DataType& dt )
{

	//vector<string> active_push_vars;
	//vector<string> active_pop_vars;
	//for(unsigned int32_t i=0; i< active_scope_list.size(); ++i){
	//	Scope* sc_ptr= active_scope_list[i];
	//	sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
	//}
	//string q_push_name = name + "_push";
	//string q_pop_name = name + "_pop";
	//map_of_active_vars_for_questions[q_push_name] = active_push_vars;
	//map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;
	vector <ActiveVariableInfo* > av_info;
	PrintActiveVariablesAtScope(active_scope_list, av_info);


	AbstractExpression * arr_sz=0;
	RangeQuestion * q=0;
	if(stack_cmpd_stmt.size()==0){
		print_err(compiler_internal_error
			, "compound statement stack is 0 when parsing"
			"a question... exiting",
				line_no, __LINE__, __FILE__  );
		exit(1);
	}
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	if(qscript_parser::flagIsAForBody_){
		//cout << "flagIsAForBody_: "
		//	<< qscript_parser::flagIsAForBody_ << endl;
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q= new RangeQuestion(QUESTION_ARR_TYPE, line_no,
				nest_lev, flagIsAForBody_,
				name, ::text_expr_vec, q_type, no_mpn, dt, xs,
				qscript_parser::for_loop_max_counter_stack,
				cmpd_stmt_ptr, av_info, question_attributes,
				mutex_range_set
			);
		qscript_parser::delete_manually_in_cleanup.push_back(
			active_scope_list[0]->insert(name.c_str(), QUESTION_ARR_TYPE, q));
		//ostringstream s1, s2;
		//arr_sz->print_expr(s1, s2);
		//cerr << "s1: " << s1.str() << ", s2: " << s2.str() << endl;
	} else {
		q= new RangeQuestion(QUESTION_TYPE, line_no,
				nest_lev, flagIsAForBody_,
				name, ::text_expr_vec, q_type, no_mpn, dt, xs, 
				cmpd_stmt_ptr, av_info, 
				question_attributes, mutex_range_set
			);
		qscript_parser::delete_manually_in_cleanup.push_back(
			active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE, q));
	}
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	//$$=q;

	question_list.push_back(q);
	/*
	cout << "question_list: questions are " << endl;
	for(int32_t i=0; i<question_list.size(); ++i){
		cout << question_list[i]->questionName_ << endl;
	}
	*/
	xs.reset();
	mutex_range_set.reset();
	// questions always get pushed in Scope level 0 as they
	// are global variables - no matter what the level of nesting
	// I need to modify the insert in Scope to
	// take a 3rd parameter which is a AbstractQuestion *
	// and store that into the symbol table
	// I should be able to retrieve that
	// AbstractQuestion* pointer later
	if (flag_next_question_start_of_block) {
		q->isStartOfBlock_ = true;
		flag_next_question_start_of_block = false;
		blk_question_start_flag[blk_question_start_flag.size()-1] = false;
		//cout << "blk_question_start_flag.size(): " << blk_question_start_flag.size() << endl;
		//cout << "At question: " << name << ", resetting flag_next_question_start_of_block = false " << endl;
		//cout << " blk_question_start_flag looks like this: " << endl;
		//for (int i=0; i<blk_question_start_flag.size(); ++i) {
		//	cout << " " <<blk_question_start_flag[i] ;
		//}
		//cout << endl;
	}
	
	return q;
}

AbstractStatement * ProcessNamedQuestion(const string &name
			, const string & q_txt , const DataType& dt
			, const string & attribute_list_name )
{

	// This is preparatory work
	// for jumping between questions
	// store
	//vector<string> active_push_vars;
	//vector<string> active_pop_vars;
	//for(unsigned int32_t i=0; i< active_scope_list.size(); ++i){
	//	Scope* sc_ptr= active_scope_list[i];
	//	sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
	//}
	//string q_push_name = name + "_push";
	//string q_pop_name = name + "_pop";
	//map_of_active_vars_for_questions[q_push_name] = active_push_vars;
	//map_of_active_vars_for_questions[q_pop_name] = active_pop_vars;
	vector <ActiveVariableInfo* > av_info;
	PrintActiveVariablesAtScope(active_scope_list, av_info);

#if 0
	bool found=false;
	struct named_range* nr_ptr = 0;
	for (uint32_t i=0; i<named_stubs_list.size(); ++i) {
		nr_ptr = named_stubs_list[i];
		if (nr_ptr->name==attribute_list_name) {
			found=true; break;
		}
	}
#endif /* 0 */
	struct named_range* nr_ptr = named_stub_exists (attribute_list_name);
        //mesg << " improve the code here - modify named_stub_exists to take a parameter and return a point to named_stub if valid";
        //LOG_MAINTAINER_MESSAGE (mesg.str());
	if (!nr_ptr) {
		print_err(compiler_sem_err, string("named_stubs_list ")
			+ attribute_list_name + string(" not found \n"), line_no,
			__LINE__, __FILE__);
                return  new ErrorStatement(qscript_parser::line_no, 
				nest_lev, flagIsAForBody_);
	}

	if (stack_cmpd_stmt.size() == 0) {
		print_err(compiler_internal_error, "compound statement stack "
			"is 0 when parsing a AbstractQuestion... exiting"
			, line_no, __LINE__, __FILE__  );
		exit(1);
	}
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	AbstractExpression * arr_sz=0;
	NamedStubQuestion* q=0;
	if(qscript_parser::flagIsAForBody_){
		//cout << "flagIsAForBody_: "
		//	<< qscript_parser::flagIsAForBody_ << endl;
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q=new NamedStubQuestion(QUESTION_ARR_TYPE, line_no
				, nest_lev, flagIsAForBody_
				, name, ::text_expr_vec, q_type, no_mpn, dt , nr_ptr
				, qscript_parser::for_loop_max_counter_stack
				, cmpd_stmt_ptr, av_info, question_attributes
				);
		qscript_parser::delete_manually_in_cleanup.push_back(
			active_scope_list[0]->insert(name.c_str(), QUESTION_ARR_TYPE, q));
	} else {
		q=new NamedStubQuestion(QUESTION_TYPE, line_no
			, nest_lev, flagIsAForBody_
			, name, ::text_expr_vec, q_type, no_mpn, dt, nr_ptr
			, cmpd_stmt_ptr, av_info, question_attributes
			);
		qscript_parser::delete_manually_in_cleanup.push_back(
				active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE, q));
	}
	question_list.push_back(q);
	//$$=q;
	++(cmpd_stmt_ptr->counterContainsQuestions_);

	if (flag_next_question_start_of_block) {
		q->isStartOfBlock_ = true;
		flag_next_question_start_of_block = false;
		//blk_question_start_flag[blk_question_start_flag.size()-1] = false;
		//cout << "blk_question_start_flag.size(): " << blk_question_start_flag.size() << endl;
		//cout << "At question: " << name << ", resetting flag_next_question_start_of_block = false " << endl;
		//cout << " blk_question_start_flag looks like this: " << endl;
		//for (int i=0; i<blk_question_start_flag.size(); ++i) {
		//	cout << " " <<blk_question_start_flag[i] ;
		//}
		//cout << endl;
	}

	return q;
}

// Close namespace
}


