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
#include "stub_pair_options.h"

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
	vector<Unary2Expression*> clear_questions_list;
	stub_pair_options current_stub_pair_options;
	



/* Line 268 of yacc.c  */
#line 124 "src/q.cpp"

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
     VIDEO = 265,
     AUDIO = 266,
     IMAGE = 267,
     GEOCODE_GMAPV3 = 268,
     VIDEO_CAPTURE = 269,
     AUDIO_CAPTURE = 270,
     IMAGE_CAPTURE = 271,
     VOID_T = 272,
     INT8_T = 273,
     INT16_T = 274,
     INT32_T = 275,
     FLOAT_T = 276,
     DOUBLE_T = 277,
     STRING_T = 278,
     IN = 279,
     FOR = 280,
     GOTO = 281,
     HIDDEN = 282,
     ALLOW_BLANK = 283,
     HELP_POPUP = 284,
     MUTEX = 285,
     OTHER = 286,
     CLEAR = 287,
     COLUMN = 288,
     ISANSWERED = 289,
     NEWCARD = 290,
     FIX = 291,
     BRAND_RANK = 292,
     DRIVERS = 293,
     CREATE_1_0_EDIT = 294,
     PAGE = 295,
     GRID_SIZE = 296,
     RANDOMIZE = 297,
     CONST = 298,
     LOGOR = 299,
     LOGAND = 300,
     NOEQ = 301,
     ISEQ = 302,
     GEQ = 303,
     LEQ = 304,
     NOT = 305,
     UMINUS = 306,
     COUNT = 307,
     FUNC_CALL = 308,
     IF = 309,
     ELSE = 310,
     STUBS_LIST = 311,
     NAMED_ATTRIBUTES = 312,
     SETDEL = 313,
     SETADD = 314,
     UNSET = 315,
     SETALL = 316,
     MAX_LENGTH = 317,
     MIN_LENGTH = 318
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 61 "src/q.ypp"

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
	struct Unary2Expression * ue2expr;





/* Line 293 of yacc.c  */
#line 242 "src/q.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 254 "src/q.cpp"

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
#define YYLAST   906

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNRULES -- Number of states.  */
#define YYNSTATES  395

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    62,    77,     2,
      45,    46,    60,    59,    49,    58,    80,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    82,    78,
      54,    47,    55,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    81,    83,    79,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    48,    50,
      51,    52,    53,    56,    57,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76
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
     110,   112,   114,   116,   118,   121,   122,   133,   137,   142,
     143,   148,   149,   157,   159,   165,   173,   176,   180,   182,
     186,   188,   193,   201,   207,   213,   221,   230,   238,   244,
     250,   256,   258,   262,   264,   269,   276,   287,   289,   290,
     293,   295,   298,   300,   302,   305,   308,   311,   315,   319,
     323,   327,   331,   334,   338,   342,   346,   350,   354,   358,
     362,   366,   370,   373,   375,   377,   379,   384,   389,   391,
     395,   399,   404,   408,   415,   420,   425,   427,   431,   433,
     438,   440,   442,   444,   446,   448,   450,   455,   457,   461,
     465,   467,   471,   473,   477,   481,   483,   484,   491,   497,
     499,   503,   505,   509,   511,   515,   517,   519,   522,   525,
     528,   531,   536,   544,   555,   565,   579,   592,   600,   611,
     622,   630,   638,   644,   650,   651,   660,   661,   668,   670,
     673
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      85,     0,    -1,     5,    97,    -1,    86,    -1,    -1,    91,
       5,    45,    88,    46,    87,    97,    -1,    89,    -1,    88,
      49,    89,    -1,    91,     5,    -1,    91,     5,    43,     3,
      44,    -1,    91,    77,     5,    -1,    -1,    94,    -1,    90,
      94,    -1,    17,    -1,    18,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    48,    -1,    91,     5,
      78,    -1,    92,    91,     5,    47,   117,    78,    -1,    91,
       5,    47,   117,    78,    -1,    91,     5,    43,   117,    44,
      78,    -1,   111,    -1,   104,    -1,    93,    -1,   125,    -1,
     127,    -1,    97,    -1,   103,    -1,    95,    -1,   133,    -1,
     105,    -1,   108,    -1,   109,    -1,   136,    -1,   139,    -1,
     134,    -1,   110,    -1,    99,    -1,    98,    -1,     1,    78,
      -1,    -1,    25,    45,   117,    78,   117,    78,   117,    46,
      96,    97,    -1,   102,    90,    79,    -1,     5,    80,    42,
      78,    -1,    -1,    40,     5,   100,    97,    -1,    -1,    40,
       5,   101,    41,    47,     3,    97,    -1,    81,    -1,    67,
      45,   117,    46,    94,    -1,    67,    45,   117,    46,    94,
      68,    94,    -1,   117,    78,    -1,    26,     5,    78,    -1,
     107,    -1,   106,    49,   107,    -1,     5,    -1,     5,    43,
     117,    44,    -1,    32,    45,   106,    49,     7,    46,    78,
      -1,    33,    45,   117,    46,    78,    -1,    35,    45,   117,
      46,    78,    -1,     5,   112,   119,    91,   122,   114,    78,
      -1,     5,   112,   119,    91,   122,   120,   114,    78,    -1,
       5,   112,   119,    91,     5,   114,    78,    -1,     5,   112,
     119,     7,    78,    -1,     5,   112,   119,   114,    78,    -1,
       5,   112,    13,   114,    78,    -1,   113,    -1,   112,    82,
     113,    -1,     7,    -1,     5,    43,   117,    44,    -1,     5,
      80,    69,    43,   117,    44,    -1,    82,     5,    43,   117,
      44,    80,    69,    43,   117,    44,    -1,     5,    -1,    -1,
      82,   115,    -1,   116,    -1,   115,   116,    -1,    27,    -1,
      28,    -1,    29,     7,    -1,    76,     3,    -1,    75,     3,
      -1,   117,    59,   117,    -1,   117,    58,   117,    -1,   117,
      60,   117,    -1,   117,    61,   117,    -1,   117,    62,   117,
      -1,    58,   117,    -1,   117,    54,   117,    -1,   117,    55,
     117,    -1,   117,    57,   117,    -1,   117,    56,   117,    -1,
     117,    53,   117,    -1,   117,    52,   117,    -1,   117,    50,
     117,    -1,   117,    51,   117,    -1,   117,    47,   117,    -1,
      63,   117,    -1,     3,    -1,     4,    -1,     5,    -1,     5,
      43,   117,    44,    -1,     5,    45,   118,    46,    -1,     7,
      -1,    45,   117,    46,    -1,   117,    24,   122,    -1,     6,
      45,     5,    46,    -1,   117,    24,     5,    -1,   117,    24,
       5,    43,   117,    44,    -1,    34,    45,     5,    46,    -1,
      65,    45,     5,    46,    -1,   117,    -1,   118,    49,   117,
      -1,     8,    -1,     9,    45,     3,    46,    -1,    10,    -1,
      12,    -1,    11,    -1,    14,    -1,    16,    -1,    15,    -1,
      30,    45,   121,    46,    -1,   120,    -1,   121,    49,   120,
      -1,     3,    58,     3,    -1,     3,    -1,    45,   123,    46,
      -1,   124,    -1,   123,    49,   124,    -1,     3,    58,     3,
      -1,     3,    -1,    -1,    69,     5,   126,    47,   129,    78,
      -1,    70,     5,    47,   128,    78,    -1,     7,    -1,   128,
      49,     7,    -1,   132,    -1,   129,    49,   132,    -1,   131,
      -1,   130,    83,   131,    -1,    30,    -1,    31,    -1,    12,
       7,    -1,    11,     7,    -1,    10,     7,    -1,     7,     3,
      -1,     7,     3,    82,   130,    -1,    71,    45,     5,    49,
       5,    46,    78,    -1,    71,    45,     5,    49,     5,    43,
     117,    44,    46,    78,    -1,    72,    45,     5,    49,    45,
       5,    46,    46,    78,    -1,    72,    45,     5,    43,   117,
      44,    49,     5,    43,   117,    44,    46,    78,    -1,    72,
      45,     5,    43,   117,    44,    49,    45,     5,    46,    46,
      78,    -1,    72,    45,     5,    49,     5,    46,    78,    -1,
      72,    45,     5,    49,     5,    43,   117,    44,    46,    78,
      -1,    72,    45,     5,    43,   117,    44,    49,   122,    46,
      78,    -1,    72,    45,     5,    49,   122,    46,    78,    -1,
      71,    45,     5,    49,   122,    46,    78,    -1,    73,    45,
       5,    46,    78,    -1,    74,    45,     5,    46,    78,    -1,
      -1,    37,   138,   135,    38,   138,    82,     3,    78,    -1,
      -1,    36,   138,   137,    38,   138,    78,    -1,     5,    -1,
     138,     5,    -1,    39,     5,    78,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   193,   193,   201,   207,   207,   242,   246,   252,   259,
     268,   277,   285,   294,   302,   303,   304,   305,   306,   307,
     308,   311,   316,   319,   321,   324,   334,   335,   336,   337,
     338,   339,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   374,   374,   394,   402,   430,
     430,   447,   447,   460,   470,   489,   530,   551,   558,   561,
     566,   569,   603,   614,   621,   629,   643,   656,   666,   672,
     677,   686,   687,   690,   693,   712,   735,   758,   782,   783,
     787,   788,   791,   794,   797,   801,   805,   812,   821,   830,
     839,   848,   857,   866,   875,   884,   893,   902,   911,   920,
     929,   938,   947,   956,   965,   973,   981,   989,  1043,  1050,
    1057,  1066,  1072,  1078,  1084,  1090,  1108,  1109,  1114,  1120,
    1123,  1126,  1129,  1132,  1135,  1138,  1143,  1148,  1149,  1153,
    1164,  1170,  1174,  1175,  1178,  1190,  1196,  1196,  1242,  1256,
    1259,  1266,  1267,  1271,  1273,  1276,  1279,  1282,  1286,  1291,
    1297,  1330,  1373,  1377,  1403,  1409,  1415,  1429,  1433,  1438,
    1444,  1450,  1457,  1460,  1465,  1465,  1489,  1489,  1512,  1513,
    1517
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INUMBER", "FNUMBER", "NAME", "TOSTRING",
  "TEXT", "SINGLE_CODED", "MP", "VIDEO", "AUDIO", "IMAGE",
  "GEOCODE_GMAPV3", "VIDEO_CAPTURE", "AUDIO_CAPTURE", "IMAGE_CAPTURE",
  "VOID_T", "INT8_T", "INT16_T", "INT32_T", "FLOAT_T", "DOUBLE_T",
  "STRING_T", "IN", "FOR", "GOTO", "HIDDEN", "ALLOW_BLANK", "HELP_POPUP",
  "MUTEX", "OTHER", "CLEAR", "COLUMN", "ISANSWERED", "NEWCARD", "FIX",
  "BRAND_RANK", "DRIVERS", "CREATE_1_0_EDIT", "PAGE", "GRID_SIZE",
  "RANDOMIZE", "'['", "']'", "'('", "')'", "'='", "CONST", "','", "LOGOR",
  "LOGAND", "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'", "'+'",
  "'*'", "'/'", "'%'", "NOT", "UMINUS", "COUNT", "FUNC_CALL", "IF", "ELSE",
  "STUBS_LIST", "NAMED_ATTRIBUTES", "SETDEL", "SETADD", "UNSET", "SETALL",
  "MAX_LENGTH", "MIN_LENGTH", "'&'", "';'", "'}'", "'.'", "'{'", "':'",
  "'|'", "$accept", "prog", "func_defn", "$@1", "decl_comma_list",
  "var_decl", "stmt_list", "datatype", "type_qual", "decl_stmt", "stmt",
  "for_loop_stmt", "$@2", "cmpd_stmt", "randomize_stmt", "page_stmt",
  "$@3", "$@4", "open_curly", "if_stmt", "expr_stmt", "goto_stmt",
  "question_expr_list", "question_expr", "clear_stmt", "column_stmt",
  "newcard_stmt", "question", "text_expr_list", "text_expr",
  "attribute_list", "attributes", "attribute", "expression", "expr_list",
  "qtype", "mutex_range", "mutex_range_list", "range_allowed_values",
  "range_list", "range", "stubs", "$@5", "named_attributes",
  "named_attribute_list", "stub_list", "stub_options_list", "stub_option",
  "stub", "stub_manip_stmts", "brand_rank_recode_stmt", "$@6",
  "fix_and_recode_stmt", "$@7", "name_list", "create_1_0_data_edit_stmt", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    91,    93,    40,    41,    61,   298,    44,
     299,   300,   301,   302,    60,    62,   303,   304,    45,    43,
      42,    47,    37,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,    38,    59,   125,
      46,   123,    58,   124
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    85,    87,    86,    88,    88,    89,    89,
      89,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    92,    93,    93,    93,    93,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    96,    95,    97,    98,   100,
      99,   101,    99,   102,   103,   103,   104,   105,   106,   106,
     107,   107,   108,   109,   110,   111,   111,   111,   111,   111,
     111,   112,   112,   113,   113,   113,   113,   113,   114,   114,
     115,   115,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   119,   119,
     119,   119,   119,   119,   119,   119,   120,   121,   121,   120,
     120,   122,   123,   123,   124,   124,   126,   125,   127,   128,
     128,   129,   129,   130,   130,   131,   131,   131,   131,   131,
     132,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   135,   134,   137,   136,   138,   138,
     139
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     7,     1,     3,     2,     5,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     6,     5,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0,    10,     3,     4,     0,
       4,     0,     7,     1,     5,     7,     2,     3,     1,     3,
       1,     4,     7,     5,     5,     7,     8,     7,     5,     5,
       5,     1,     3,     1,     4,     6,    10,     1,     0,     2,
       1,     2,     1,     1,     2,     2,     2,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     1,     4,     4,     1,     3,
       3,     4,     3,     6,     4,     4,     1,     3,     1,     4,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     3,
       1,     3,     1,     3,     3,     1,     0,     6,     5,     1,
       3,     1,     3,     1,     3,     1,     1,     2,     2,     2,
       2,     4,     7,    10,     9,    13,    12,     7,    10,    10,
       7,     7,     5,     5,     0,     8,     0,     6,     1,     2,
       3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    15,    16,    17,    18,    19,    20,     0,
       3,     0,    53,     2,     0,     1,     0,     0,   103,   104,
     105,     0,   108,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    12,
      33,    31,    43,    42,    32,    27,    35,    36,    37,    41,
      26,     0,    29,    30,    34,    40,    38,    39,    11,    44,
      77,    73,     0,     0,     0,     0,     0,    71,     0,     0,
       0,     0,     0,     0,     0,   168,   166,   164,     0,    49,
     105,     0,    92,   102,     0,     0,   136,     0,     0,     0,
       0,     0,    47,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,     0,     6,     0,     0,     0,     0,   116,     0,
       0,     0,   118,     0,   120,   122,   121,    78,   123,   125,
     124,     0,    78,     0,     0,    57,    60,     0,    58,     0,
       0,     0,   169,     0,     0,   170,     0,     0,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
       0,   112,     0,   110,   101,    99,   100,    98,    97,    93,
      94,    96,    95,    88,    87,    89,    90,    91,     4,    11,
       8,     0,     0,     0,   106,   107,     0,    48,     0,     0,
       0,     0,    72,     0,     0,     0,   111,     0,     0,     0,
       0,   114,     0,     0,     0,    50,     0,   115,     0,     0,
     139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,     0,   132,     0,     7,     0,    10,    74,     0,
     117,     0,     0,    82,    83,     0,     0,     0,    79,    80,
      70,    68,    78,    78,    69,     0,     0,     0,    59,    63,
      64,     0,     0,     0,    54,     0,     0,   141,     0,   138,
       0,     0,     0,     0,     0,     0,   162,   163,     0,    24,
       0,     0,     0,   131,     0,     5,     0,     0,     0,   119,
      84,    86,    85,    81,     0,   130,     0,     0,    78,     0,
      61,     0,   167,     0,     0,     0,   150,     0,   137,   140,
       0,     0,     0,     0,     0,     0,     0,     0,    25,    23,
     113,   134,   133,     9,    75,     0,    67,     0,     0,    65,
       0,     0,    62,     0,    52,    55,     0,   142,     0,   152,
     161,     0,     0,   157,     0,   160,     0,   129,   127,     0,
      66,    45,   165,     0,     0,     0,   145,   146,   151,   143,
       0,     0,     0,     0,     0,     0,     0,   126,     0,     0,
     149,   148,   147,     0,     0,     0,     0,     0,     0,   154,
       0,   128,    46,   144,   153,     0,     0,   159,   158,    76,
       0,     0,     0,   156,   155
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,   234,   122,   123,    45,    46,    47,    48,
      49,    50,   369,    51,    52,    53,   156,   157,    14,    54,
      55,    56,   147,   148,    57,    58,    59,    60,    76,    77,
     201,   248,   249,    61,   129,   142,   298,   349,   173,   232,
     233,    62,   161,    63,   221,   266,   358,   359,   267,    64,
      65,   154,    66,   153,    86,    67
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -318
static const yytype_int16 yypact[] =
{
     182,   -69,  -318,  -318,  -318,  -318,  -318,  -318,  -318,    29,
    -318,    43,  -318,  -318,   319,  -318,    69,   -24,  -318,  -318,
      12,    70,  -318,    83,   146,   116,   117,   120,   128,   172,
     172,   174,   176,    95,  -318,    95,    95,   137,   138,   179,
     183,   144,   145,   147,   148,   218,   189,   104,  -318,  -318,
    -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,
    -318,   255,  -318,  -318,  -318,  -318,  -318,  -318,   104,  -318,
      66,  -318,    95,    95,   164,   191,    56,  -318,   215,    95,
     150,   221,    95,   222,    95,  -318,   224,   224,   152,   190,
     107,   507,   208,   208,   229,    95,  -318,   195,   240,   241,
     242,   243,  -318,  -318,    61,   244,     4,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,  -318,   -22,  -318,    20,    95,   187,   526,   844,    -7,
     181,   217,  -318,   216,  -318,  -318,  -318,   180,  -318,  -318,
    -318,     8,    13,   223,   351,  -318,   225,   226,  -318,   547,
     227,   565,  -318,   232,   233,  -318,   -69,   231,  -318,   228,
     586,   230,   257,   235,    -5,   234,   247,    95,    95,  -318,
     239,   251,   292,  -318,   844,   403,   156,   361,   361,   109,
     109,   109,   109,    81,    81,   208,   208,   208,  -318,   104,
     253,   293,   605,   258,  -318,  -318,    95,  -318,    95,   297,
      31,   249,  -318,   250,    11,   252,  -318,    95,    95,   149,
     254,  -318,   268,   172,   172,  -318,   271,  -318,   319,   312,
    -318,    54,    16,    95,    17,   269,   270,   626,   390,    95,
      95,   246,    -3,  -318,   -69,  -318,   318,  -318,  -318,    95,
     844,   645,   283,  -318,  -318,   324,   332,   346,    31,  -318,
    -318,  -318,   180,     7,  -318,   429,   666,   304,  -318,  -318,
    -318,    18,     9,   354,   294,   357,    71,  -318,   356,  -318,
      73,   315,   685,    91,   154,   320,  -318,  -318,   287,  -318,
     468,   706,   366,  -318,   292,  -318,   326,   725,   291,  -318,
    -318,  -318,  -318,  -318,   295,   314,   329,   298,   180,    95,
    -318,   300,  -318,   376,   -69,   319,   299,   312,  -318,  -318,
      95,   302,   305,   338,    95,   316,   349,   321,  -318,  -318,
    -318,  -318,  -318,  -318,  -318,   327,  -318,   394,    15,  -318,
     347,   746,  -318,   348,  -318,  -318,   100,  -318,   765,  -318,
    -318,    68,   786,  -318,   378,  -318,   385,  -318,  -318,    98,
    -318,  -318,  -318,   423,   424,   425,  -318,  -318,   350,  -318,
     388,   392,   169,   393,   420,   358,    95,  -318,    15,   -69,
    -318,  -318,  -318,   100,   360,    95,   421,   391,   395,  -318,
     805,  -318,  -318,  -318,  -318,   826,   426,  -318,  -318,  -318,
     428,   397,   399,  -318,  -318
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -318,  -318,  -318,  -318,  -318,   281,  -318,     6,  -318,  -318,
     -40,  -318,  -318,    -1,  -318,  -318,  -318,  -318,  -318,  -318,
    -318,  -318,  -318,   262,  -318,  -318,  -318,  -318,  -318,   337,
    -135,  -318,   245,   -32,  -318,  -318,  -317,  -318,  -196,  -318,
     210,  -318,  -318,  -318,  -318,  -318,  -318,   122,   192,  -318,
    -318,  -318,  -318,  -318,   -28,  -318
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -52
static const yytype_int16 yytable[] =
{
      13,    91,    87,    92,    93,   103,    11,   205,   253,   171,
     295,   348,    12,    70,   152,    71,   252,    70,   295,    71,
     203,   270,   273,   152,   188,   190,   271,   189,   275,    15,
       2,     3,     4,     5,     6,     7,     8,   296,   223,   195,
     127,   128,   196,   283,   224,   296,   284,   144,    16,   172,
     149,   381,   151,   105,    69,    72,   172,    73,   243,   244,
     245,   172,   274,   160,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   361,   124,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   200,
      75,   303,    74,   192,    75,   200,   302,   191,    18,    19,
      90,    21,    22,   268,   167,   106,   246,   247,   168,   125,
     353,   354,   355,   362,    68,    78,   310,   294,   297,   311,
     307,     2,     3,     4,     5,     6,     7,     8,    79,    27,
     356,   357,   269,   106,   314,   227,   228,   315,   141,   169,
      33,   118,   119,   120,   367,   363,   126,   368,   204,   308,
      72,    80,    73,    35,   146,   215,   257,   231,    36,   316,
      37,    81,    82,   330,   240,    83,   241,   116,   117,   118,
     119,   120,   231,    84,   376,   255,   256,    85,   264,    88,
     106,    89,    94,    95,    96,   261,   262,     1,    97,    98,
      99,   272,   100,   101,   104,   124,   131,   280,   281,     2,
       3,     4,     5,     6,     7,     8,   130,   287,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,    17,
     143,    18,    19,    20,    21,    22,   146,   150,   145,   152,
     155,   -51,   106,   285,   159,     2,     3,     4,     5,     6,
       7,     8,   162,    23,    24,   163,   164,   165,   166,   170,
      25,    26,    27,    28,    29,    30,   193,    31,    32,   197,
     198,   199,   200,    33,   220,   335,    34,   331,   208,   206,
     213,   214,   216,   211,   217,   209,    35,   219,   338,   106,
     225,    36,   342,    37,   222,    38,   229,    39,    40,    41,
      42,    43,    44,   226,   230,   231,   236,   102,   237,    12,
     242,   239,   107,   334,   282,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   263,   265,
      17,   286,    18,    19,    20,    21,    22,   250,   251,   289,
     254,   290,   259,   121,   380,   291,     2,     3,     4,     5,
       6,     7,     8,   385,    23,    24,   260,   276,   277,   292,
     301,    25,    26,    27,    28,    29,    30,   304,    31,    32,
     306,   312,   305,   309,    33,   318,   317,    34,   382,   321,
     323,   325,   327,   326,   328,   106,   329,    35,   332,   333,
     339,   336,    36,   340,    37,   106,    38,   341,    39,    40,
      41,    42,    43,    44,   343,   344,   346,   347,   107,   345,
      12,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   106,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   365,   350,   352,   106,   366,   207,
     370,   371,   372,   373,   374,   375,   379,   107,   384,   377,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   106,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   378,   386,   279,   387,
     235,   258,   391,   388,   392,   393,   107,   394,   202,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   106,   293,   322,   383,     0,     0,     0,   337,
       0,     0,     0,     0,     0,     0,     0,   299,     0,     0,
       0,     0,     0,     0,     0,   107,     0,     0,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   319,     0,     0,     0,
     106,     0,     0,   158,   107,     0,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     194,   106,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   106,
       0,     0,     0,   210,   107,     0,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     106,   212,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     0,   106,
       0,     0,   218,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   238,
     106,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     0,   106,
     278,     0,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   288,
     106,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     0,   106,
     300,     0,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   313,
     106,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     0,   106,
     320,     0,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   324,
     106,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     0,   106,
       0,     0,   351,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   360,
     106,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     0,   106,
     364,     0,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   389,
     106,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   106,     0,
     390,     0,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,     0,
       0,   107,     0,     0,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-318))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    33,    30,    35,    36,    45,     0,   142,   204,     5,
       3,   328,    81,     5,     5,     7,     5,     5,     3,     7,
       7,     5,     5,     5,    46,     5,   222,    49,   224,     0,
      17,    18,    19,    20,    21,    22,    23,    30,    43,    46,
      72,    73,    49,    46,    49,    30,    49,    79,     5,    45,
      82,   368,    84,    47,    78,    43,    45,    45,    27,    28,
      29,    45,    45,    95,     8,     9,    10,    11,    12,    13,
      14,    15,    16,     5,    68,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,    82,
      82,    82,    80,   125,    82,    82,    78,    77,     3,     4,
       5,     6,     7,    49,    43,    24,    75,    76,    47,    43,
      10,    11,    12,    45,    45,    45,    43,   252,   253,    46,
      49,    17,    18,    19,    20,    21,    22,    23,    45,    34,
      30,    31,    78,    24,    43,   167,   168,    46,    82,    78,
      45,    60,    61,    62,    46,   341,    80,    49,   142,    78,
      43,     5,    45,    58,     5,   156,     7,     3,    63,     5,
      65,    45,    45,   298,   196,    45,   198,    58,    59,    60,
      61,    62,     3,    45,     5,   207,   208,     5,   218,     5,
      24,     5,    45,    45,     5,   213,   214,     5,     5,    45,
      45,   223,    45,    45,     5,   189,     5,   229,   230,    17,
      18,    19,    20,    21,    22,    23,    42,   239,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     1,
       5,     3,     4,     5,     6,     7,     5,     5,    78,     5,
      78,    41,    24,   234,     5,    17,    18,    19,    20,    21,
      22,    23,    47,    25,    26,     5,     5,     5,     5,     5,
      32,    33,    34,    35,    36,    37,    69,    39,    40,    78,
      43,    45,    82,    45,     7,   305,    48,   299,    43,    46,
      38,    38,    41,    46,    46,    49,    58,    47,   310,    24,
      46,    63,   314,    65,    49,    67,    47,    69,    70,    71,
      72,    73,    74,    46,    43,     3,    43,    79,     5,    81,
       3,    43,    47,   304,    58,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    47,     7,
       1,     3,     3,     4,     5,     6,     7,    78,    78,    46,
      78,     7,    78,    78,   366,     3,    17,    18,    19,    20,
      21,    22,    23,   375,    25,    26,    78,    78,    78,     3,
      46,    32,    33,    34,    35,    36,    37,     3,    39,    40,
       3,    46,    68,     7,    45,    78,    46,    48,   369,     3,
      44,    80,    58,    78,    45,    24,    78,    58,    78,     3,
      78,    82,    63,    78,    65,    24,    67,    49,    69,    70,
      71,    72,    73,    74,    78,    46,    69,     3,    47,    78,
      81,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    24,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    46,    78,    78,    24,    43,    78,
       7,     7,     7,    83,    46,    43,    78,    47,    78,    46,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    24,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    46,    46,    78,    78,
     189,   209,    46,    78,    46,    78,    47,    78,   141,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    24,   248,   284,   373,    -1,    -1,    -1,   307,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      24,    -1,    -1,    46,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      44,    24,    -1,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    24,
      -1,    -1,    -1,    46,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      24,    46,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    24,
      -1,    -1,    46,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    44,
      24,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    24,
      44,    -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    44,
      24,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    24,
      44,    -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    44,
      24,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    24,
      44,    -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    44,
      24,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    24,
      -1,    -1,    46,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    44,
      24,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    24,
      44,    -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    44,
      24,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    24,    -1,
      44,    -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    47,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    17,    18,    19,    20,    21,    22,    23,    85,
      86,    91,    81,    97,   102,     0,     5,     1,     3,     4,
       5,     6,     7,    25,    26,    32,    33,    34,    35,    36,
      37,    39,    40,    45,    48,    58,    63,    65,    67,    69,
      70,    71,    72,    73,    74,    90,    91,    92,    93,    94,
      95,    97,    98,    99,   103,   104,   105,   108,   109,   110,
     111,   117,   125,   127,   133,   134,   136,   139,    45,    78,
       5,     7,    43,    45,    80,    82,   112,   113,    45,    45,
       5,    45,    45,    45,    45,     5,   138,   138,     5,     5,
       5,   117,   117,   117,    45,    45,     5,     5,    45,    45,
      45,    45,    79,    94,     5,    91,    24,    47,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    78,    88,    89,    91,    43,    80,   117,   117,   118,
      42,     5,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    82,   119,     5,   117,    78,     5,   106,   107,   117,
       5,   117,     5,   137,   135,    78,   100,   101,    46,     5,
     117,   126,    47,     5,     5,     5,     5,    43,    47,    78,
       5,     5,    45,   122,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,    46,    49,
       5,    77,   117,    69,    44,    46,    49,    78,    43,    45,
      82,   114,   113,     7,    91,   114,    46,    78,    43,    49,
      46,    46,    46,    38,    38,    97,    41,    46,    46,    47,
       7,   128,    49,    43,    49,    46,    46,   117,   117,    47,
      43,     3,   123,   124,    87,    89,    43,     5,    44,    43,
     117,   117,     3,    27,    28,    29,    75,    76,   115,   116,
      78,    78,     5,   122,    78,   117,   117,     7,   107,    78,
      78,   138,   138,    47,    94,     7,   129,   132,    49,    78,
       5,   122,   117,     5,    45,   122,    78,    78,    44,    78,
     117,   117,    58,    46,    49,    97,     3,   117,    44,    46,
       7,     3,     3,   116,   114,     3,    30,   114,   120,    78,
      44,    46,    78,    82,     3,    68,     3,    49,    78,     7,
      43,    46,    46,    44,    43,    46,     5,    46,    78,    78,
      44,     3,   124,    44,    44,    80,    78,    58,    45,    78,
     114,   117,    78,     3,    97,    94,    82,   132,   117,    78,
      78,    49,   117,    78,    46,    78,    69,     3,   120,   121,
      78,    46,    78,    10,    11,    12,    30,    31,   130,   131,
      44,     5,    45,   122,    44,    46,    43,    46,    49,    96,
       7,     7,     7,    83,    46,    43,     5,    46,    46,    78,
     117,   120,    97,   131,    78,   117,    46,    78,    78,    44,
      44,    46,    46,    78,    78
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
#line 193 "src/q.ypp"
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
#line 201 "src/q.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 207 "src/q.ypp"
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
#line 218 "src/q.ypp"
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
#line 242 "src/q.ypp"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 246 "src/q.ypp"
    {
		(yyval.v_list)=qscript_parser::link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 252 "src/q.ypp"
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
#line 259 "src/q.ypp"
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
#line 268 "src/q.ypp"
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
#line 277 "src/q.ypp"
    {
		(yyval.v_list)=0;
		}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 285 "src/q.ypp"
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
#line 294 "src/q.ypp"
    {
		(yyvsp[(1) - (2)].stmt) -> next_ = (yyvsp[(2) - (2)].stmt);
		(yyvsp[(2) - (2)].stmt) -> prev_ = (yyvsp[(1) - (2)].stmt);
		(yyval.stmt) = (yyvsp[(2) - (2)].stmt);
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 311 "src/q.ypp"
    {
		   (yyval.type_qual) = CONST_QUAL;
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 316 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 319 "src/q.ypp"
    {
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 321 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 324 "src/q.ypp"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].expr)/*, line_no*/);
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 339 "src/q.ypp"
    {
		(yyval.stmt) = (yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 354 "src/q.ypp"
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

  case 45:

/* Line 1806 of yacc.c  */
#line 374 "src/q.ypp"
    {
		++qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.push_back ((yyvsp[(5) - (8)].expr));
	        qscript_parser::ParseSpecialCaseAndAttachMaxBounds ((yyvsp[(5) - (8)].expr));
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 378 "src/q.ypp"
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

  case 47:

/* Line 1806 of yacc.c  */
#line 394 "src/q.ypp"
    {
		(yyval.c_stmt) = qscript_parser::ProcessCompoundStatement((yyvsp[(1) - (3)].c_stmt), (yyvsp[(2) - (3)].stmt));
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 402 "src/q.ypp"
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

  case 49:

/* Line 1806 of yacc.c  */
#line 430 "src/q.ypp"
    {
	 	qscript_parser::globalActivePageName_ = (yyvsp[(2) - (2)].name);
	 	// cout << "globalActivePageName_: " << qscript_parser::globalActivePageName_ << endl;
	 }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 433 "src/q.ypp"
    {
		std::stringstream mesg;
		mesg << "Need to add check that names for pages are unique";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		string page_name ((yyvsp[(2) - (4)].name));
		PageStatement * a_page =
			new PageStatement (PAGE_STMT,
					qscript_parser::line_no,
					qscript_parser::nest_lev,
					qscript_parser::flagIsAForBody_,
					page_name, (yyvsp[(4) - (4)].c_stmt));
		(yyval.stmt) = a_page;
		qscript_parser::globalActivePageName_ = string("");
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 447 "src/q.ypp"
    {qscript_parser::globalActivePageName_ = (yyvsp[(2) - (2)].name);}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 447 "src/q.ypp"
    {
		string page_name ((yyvsp[(2) - (7)].name));
		int32_t grid_size = (yyvsp[(6) - (7)].ival);
		PageStatement * a_page =
			new PageStatement (PAGE_STMT,
					qscript_parser::line_no,
					qscript_parser::nest_lev,
					qscript_parser::flagIsAForBody_,
					page_name, (yyvsp[(7) - (7)].c_stmt), grid_size);
		(yyval.stmt) = a_page;
		qscript_parser::globalActivePageName_ = string("");
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 460 "src/q.ypp"
    {
		CompoundStatement * cmpdStmt = qscript_parser::ProcessOpenCurly();
		//qscript_parser::compound_body_stack.push_back(cmpdStmt);
		//cmpdStmt->nestedCompoundStatementStack_=qscript_parser::compound_body_stack;
		(yyval.c_stmt)=cmpdStmt;
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 470 "src/q.ypp"
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

  case 55:

/* Line 1806 of yacc.c  */
#line 489 "src/q.ypp"
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

  case 56:

/* Line 1806 of yacc.c  */
#line 531 "src/q.ypp"
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

  case 57:

/* Line 1806 of yacc.c  */
#line 551 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new GotoStatement(GOTO_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(2) - (3)].name));
		// free($2); ? is this required here
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 558 "src/q.ypp"
    {
			clear_questions_list.push_back ((yyvsp[(1) - (1)].ue2expr));
		}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 561 "src/q.ypp"
    {
		  	clear_questions_list.push_back ((yyvsp[(3) - (3)].ue2expr));
		}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 566 "src/q.ypp"
    {
		(yyval.ue2expr) = new Unary2Expression ((yyvsp[(1) - (1)].name), oper_name);
	     }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 569 "src/q.ypp"
    {
		(yyval.ue2expr) = new Unary2Expression (oper_arrderef, (yyvsp[(1) - (4)].name), (yyvsp[(3) - (4)].expr));
		}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 603 "src/q.ypp"
    {
	  	//$$ = 0;
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement (CLEAR_STMT, qscript_parser::line_no,
			nest_lev, flagIsAForBody_,
			clear_questions_list, (yyvsp[(5) - (7)].text_buf));
		clear_questions_list.clear();
	  }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 614 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ColumnStatement(COLUMN_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr));
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 621 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new NewCardStatement(COLUMN_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr));
	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 629 "src/q.ypp"
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

  case 66:

/* Line 1806 of yacc.c  */
#line 643 "src/q.ypp"
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

  case 67:

/* Line 1806 of yacc.c  */
#line 656 "src/q.ypp"
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

  case 68:

/* Line 1806 of yacc.c  */
#line 666 "src/q.ypp"
    {
		string path_to_media ((yyvsp[(4) - (5)].text_buf));
		(yyval.stmt) = qscript_parser::ProcessVideoQuestion((yyvsp[(1) - (5)].name), "dummy question text", path_to_media);
		text_expr_vec.clear();
		question_attributes.Reset();
	}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 672 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::ProcessCaptureQuestion((yyvsp[(1) - (5)].name), "dummy question text");
		text_expr_vec.clear();
		question_attributes.Reset();
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 677 "src/q.ypp"
    {
		qscript_parser::q_type = geocode_gmapv3;
		(yyval.stmt) = qscript_parser::ProcessGeocodeQuestion((yyvsp[(1) - (5)].name), qscript_parser::q_type);
		qscript_parser::has_a_geocode_question  = true;
		question_attributes.Reset();
		text_expr_vec.clear();
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 690 "src/q.ypp"
    {
		text_expr_vec.push_back (new TextExpression(string((yyvsp[(1) - (1)].text_buf))));
	}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 693 "src/q.ypp"
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

  case 75:

/* Line 1806 of yacc.c  */
#line 712 "src/q.ypp"
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

  case 76:

/* Line 1806 of yacc.c  */
#line 735 "src/q.ypp"
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

  case 77:

/* Line 1806 of yacc.c  */
#line 758 "src/q.ypp"
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

  case 82:

/* Line 1806 of yacc.c  */
#line 791 "src/q.ypp"
    {
		question_attributes.setHidden();
	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 794 "src/q.ypp"
    {
		question_attributes.setAllowBlank();
	}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 797 "src/q.ypp"
    {
		// just parse in this branch - we can safely ignore the help text
		//question_attributes.setHelpText($2);
	}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 801 "src/q.ypp"
    {
		// just parse in this branch - we can safely ignore the help text
		//question_attributes.setMinLength($2);
	}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 805 "src/q.ypp"
    {
		// just parse in this branch - we can safely ignore the help text
		//question_attributes.setMaxLength($2);
	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 812 "src/q.ypp"
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

  case 88:

/* Line 1806 of yacc.c  */
#line 821 "src/q.ypp"
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

  case 89:

/* Line 1806 of yacc.c  */
#line 830 "src/q.ypp"
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

  case 90:

/* Line 1806 of yacc.c  */
#line 839 "src/q.ypp"
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

  case 91:

/* Line 1806 of yacc.c  */
#line 848 "src/q.ypp"
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

  case 92:

/* Line 1806 of yacc.c  */
#line 857 "src/q.ypp"
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

  case 93:

/* Line 1806 of yacc.c  */
#line 866 "src/q.ypp"
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

  case 94:

/* Line 1806 of yacc.c  */
#line 875 "src/q.ypp"
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

  case 95:

/* Line 1806 of yacc.c  */
#line 884 "src/q.ypp"
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

  case 96:

/* Line 1806 of yacc.c  */
#line 893 "src/q.ypp"
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

  case 97:

/* Line 1806 of yacc.c  */
#line 902 "src/q.ypp"
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

  case 98:

/* Line 1806 of yacc.c  */
#line 911 "src/q.ypp"
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

  case 99:

/* Line 1806 of yacc.c  */
#line 920 "src/q.ypp"
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

  case 100:

/* Line 1806 of yacc.c  */
#line 929 "src/q.ypp"
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

  case 101:

/* Line 1806 of yacc.c  */
#line 938 "src/q.ypp"
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

  case 102:

/* Line 1806 of yacc.c  */
#line 947 "src/q.ypp"
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

  case 103:

/* Line 1806 of yacc.c  */
#line 956 "src/q.ypp"
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

  case 104:

/* Line 1806 of yacc.c  */
#line 965 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].dval));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 973 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].name), oper_name );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 981 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		(yyval.expr) = new Unary2Expression(oper_arrderef, (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 989 "src/q.ypp"
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

  case 108:

/* Line 1806 of yacc.c  */
#line 1043 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1050 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (3)].expr), oper_parexp );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1057 "src/q.ypp"
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

  case 111:

/* Line 1806 of yacc.c  */
#line 1066 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression((yyvsp[(3) - (4)].name), oper_to_string);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1072 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].name), 0, oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1078 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (6)].expr), (yyvsp[(3) - (6)].name), (yyvsp[(5) - (6)].expr), oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1084 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_isanswered);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1090 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_count);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1108 "src/q.ypp"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1109 "src/q.ypp"
    {
		(yyval.expr)=qscript_parser::link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1114 "src/q.ypp"
    {
	       qscript_parser::q_type = spn;
	       // we need this =1 when generating
	       // code for flat file creation
		qscript_parser::no_mpn = 1;
	}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1120 "src/q.ypp"
    { qscript_parser::q_type = mpn;
		qscript_parser::no_mpn = (yyvsp[(3) - (4)].ival);
	}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1123 "src/q.ypp"
    {
	       qscript_parser::q_type = video;
	}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1126 "src/q.ypp"
    {
	       qscript_parser::q_type = image;
	}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1129 "src/q.ypp"
    {
	       qscript_parser::q_type = audio;
	}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1132 "src/q.ypp"
    {
	       qscript_parser::q_type = video_capture;
	}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1135 "src/q.ypp"
    {
	       qscript_parser::q_type = image_capture;
	}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1138 "src/q.ypp"
    {
	       qscript_parser::q_type = audio_capture;
	}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1143 "src/q.ypp"
    {
		     qscript_parser::has_mutex_range = true;
	     }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1153 "src/q.ypp"
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

  case 130:

/* Line 1806 of yacc.c  */
#line 1164 "src/q.ypp"
    {
		qscript_parser::mutex_range_set.add_indiv((yyvsp[(1) - (1)].ival));
	}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1170 "src/q.ypp"
    { }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1178 "src/q.ypp"
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

  case 135:

/* Line 1806 of yacc.c  */
#line 1190 "src/q.ypp"
    {
		//qscript_parser::xs.indiv.insert($1);
		qscript_parser::xs.add_indiv((yyvsp[(1) - (1)].ival));
	}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1196 "src/q.ypp"
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

  case 137:

/* Line 1806 of yacc.c  */
#line 1217 "src/q.ypp"
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

  case 138:

/* Line 1806 of yacc.c  */
#line 1242 "src/q.ypp"
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

  case 139:

/* Line 1806 of yacc.c  */
#line 1256 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(1) - (1)].text_buf));
	}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1259 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(3) - (3)].text_buf));
	}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1271 "src/q.ypp"
    {
		 }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1276 "src/q.ypp"
    {
		current_stub_pair_options.is_mutex = true;
	   }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1279 "src/q.ypp"
    {
		current_stub_pair_options.is_other_specify = true;
	   }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1282 "src/q.ypp"
    {
	   	current_stub_pair_options.stub_media_type = stub_pair_options::image;
	   	current_stub_pair_options.url = (yyvsp[(2) - (2)].text_buf);
	   }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1286 "src/q.ypp"
    {
	   	current_stub_pair_options.stub_media_type = stub_pair_options::audio;
	   	current_stub_pair_options.url = (yyvsp[(2) - (2)].text_buf);
		}
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1291 "src/q.ypp"
    {
	   	current_stub_pair_options.stub_media_type = stub_pair_options::video;
	   	current_stub_pair_options.url = (yyvsp[(2) - (2)].text_buf);
		}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1297 "src/q.ypp"
    {
		string s1 = (yyvsp[(1) - (2)].text_buf);
		int32_t code = (yyvsp[(2) - (2)].ival);
		qscript_parser::do_stub_pair_checks (s1, code, current_stub_pair_options);
		/*
		using qscript_parser::stub_list;
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
		*/
	}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1330 "src/q.ypp"
    {
		string s1 = (yyvsp[(1) - (4)].text_buf);
		int32_t code = (yyvsp[(2) - (4)].ival);
		cout << "parsed stub with options" << endl;
		qscript_parser::do_stub_pair_checks (s1, code, current_stub_pair_options);
		current_stub_pair_options.reset();
	}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1373 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), 0, (yyvsp[(5) - (7)].name), 0);
	}
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1377 "src/q.ypp"
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

  case 154:

/* Line 1806 of yacc.c  */
#line 1403 "src/q.ypp"
    {
                // 2nd NAME is an expression
                Unary2Expression * un2e = new Unary2Expression ((yyvsp[(6) - (9)].name), oper_name);
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (9)].name), 0, un2e);
	}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1409 "src/q.ypp"
    {
		cout << __LINE__ << "|^: reached here" << endl;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (13)].name), (yyvsp[(5) - (13)].expr), (yyvsp[(8) - (13)].name), (yyvsp[(10) - (13)].expr));
        }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1415 "src/q.ypp"
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

  case 157:

/* Line 1806 of yacc.c  */
#line 1429 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), 0, (yyvsp[(5) - (7)].name), 0);
	}
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 1433 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), 0, (yyvsp[(5) - (10)].name), (yyvsp[(7) - (10)].expr));
		//cout << "reached here" << endl;		
	}
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1438 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), (yyvsp[(5) - (10)].expr), xs);
		xs.reset();
        }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 1444 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), 0, xs);
		xs.reset();
	}
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 1450 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), 0, xs);
		//using qscript_parser::xs;
		xs.reset();
	}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 1457 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_UNSET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 1460 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_SET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 1465 "src/q.ypp"
    { recode_list = name_list; name_list.clear(); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 1466 "src/q.ypp"
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

  case 166:

/* Line 1806 of yacc.c  */
#line 1489 "src/q.ypp"
    { recode_list = name_list; name_list.clear(); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 1490 "src/q.ypp"
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

  case 168:

/* Line 1806 of yacc.c  */
#line 1512 "src/q.ypp"
    { name_list.push_back((yyvsp[(1) - (1)].name)); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 1513 "src/q.ypp"
    { name_list.push_back((yyvsp[(2) - (2)].name)); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 1517 "src/q.ypp"
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
#line 3838 "src/q.cpp"
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
#line 1530 "src/q.ypp"



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
	if (qscript_parser::page_nest_lev == 1) {
		qscript_parser::page_nest_lev = 0;
	} else if (qscript_parser::page_nest_lev > 1) {
		print_err(compiler_internal_error
			, "Error: page_nest_lev should never be more than 1 "
			   "ProcessCompoundStatement : "
			"... exiting"
			, line_no, __LINE__, __FILE__  );
		exit (1);
	}

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
		if (nr_ptr->name == attribute_list_name) {
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
	if (qscript_parser::flagIsAForBody_) {
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

AbstractStatement * ProcessCaptureQuestion (const string &name
	, const string & q_txt)
{
	vector <ActiveVariableInfo* > av_info;
	PrintActiveVariablesAtScope(active_scope_list, av_info);
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	VideoCaptureQuestion* q=0;

#if 0
	AbstractExpression * arr_sz=0;
	if (q_type == video_capture) {
		cout << "Got an video_capture question" << endl;
		q = new VideoCaptureQuestion (QUESTION_TYPE, line_no
				, nest_lev, flagIsAForBody_
				, name, ::text_expr_vec, q_type
				, cmpd_stmt_ptr
				, av_info, question_attributes);
	} else if (q_type == audio_capture) {
		//q = new AudioCaptureQuestion (QUESTION_TYPE, line_no
		//		, nest_lev, flagIsAForBody_
		//		, name, ::text_expr_vec, q_type
		//		, cmpd_stmt_ptr
		//		, av_info, question_attributes);
		cout << "Got an audio_capture question" << endl;
		q = new VideoCaptureQuestion (QUESTION_TYPE, line_no
				, nest_lev, flagIsAForBody_
				, name, ::text_expr_vec, q_type
				, cmpd_stmt_ptr
				, av_info, question_attributes);
	} else if (q_type == image_capture) {
		cout << "Got an image_capture question" << endl;
		q = new VideoCaptureQuestion (QUESTION_TYPE, line_no
				, nest_lev, flagIsAForBody_
				, name, ::text_expr_vec, q_type
				, cmpd_stmt_ptr
				, av_info, question_attributes);
	} else {
		std::stringstream err_mesg;
		err_mesg << " Question has to be of video, audio or image type";
		print_err (compiler_sem_err , err_mesg.str().c_str(),
				qscript_parser::line_no, __LINE__, __FILE__  );
	}
#endif /* 0 */
	AbstractExpression * arr_sz=0;
	if (qscript_parser::flagIsAForBody_) {
		arr_sz = qscript_parser::recurse_for_index(
			qscript_parser::for_loop_max_counter_stack.size()-1);
		q = new VideoCaptureQuestion (QUESTION_ARR_TYPE, line_no
				, nest_lev, flagIsAForBody_
				, name, ::text_expr_vec, q_type
				, qscript_parser::for_loop_max_counter_stack
				, cmpd_stmt_ptr
				, av_info, question_attributes);
	} else {
		if (q_type == video_capture || q_type == audio_capture || q_type == image_capture) {
			//cout << "Got an video_capture question" << endl;
			q = new VideoCaptureQuestion (QUESTION_TYPE, line_no
					, nest_lev, flagIsAForBody_
					, name, ::text_expr_vec, q_type
					, cmpd_stmt_ptr
					, av_info, question_attributes);
		} else {
			std::stringstream err_mesg;
			err_mesg << " Question has to be of video, audio or image type";
			print_err (compiler_sem_err , err_mesg.str().c_str(),
					qscript_parser::line_no, __LINE__, __FILE__  );
		}
	}
	question_list.push_back(q);
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	if (flag_next_question_start_of_block) {
		q->isStartOfBlock_ = true;
		flag_next_question_start_of_block = false;
	}
	return q;
}



AbstractStatement * ProcessVideoQuestion (const string &name
	, const string & q_txt //, const DataType& dt
	, const string & path_to_media)
{
	//($1, "dummy question text", $4, $5);
	vector <ActiveVariableInfo* > av_info;
	PrintActiveVariablesAtScope(active_scope_list, av_info);
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();
	VideoQuestion* q=0;

	if (q_type == video || q_type == audio || q_type == image) {
	} else {
		std::stringstream err_mesg;
		err_mesg << " Question has to be of video, audio or image type";
		print_err (compiler_sem_err , err_mesg.str().c_str(),
				qscript_parser::line_no, __LINE__, __FILE__  );
	}

	if (qscript_parser::flagIsAForBody_) {
		cerr << " Video within for loops not yet implemented - exiting"
			<< endl;
		exit (1);
	} else {
		q = new VideoQuestion (QUESTION_TYPE, line_no
				, nest_lev, flagIsAForBody_
				, name, ::text_expr_vec, q_type
				, cmpd_stmt_ptr
				, av_info, question_attributes
				, path_to_media
				);
		question_list.push_back(q);
	}
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	if (flag_next_question_start_of_block) {
		q->isStartOfBlock_ = true;
		flag_next_question_start_of_block = false;
	}
	return q;

}

AbstractStatement * ProcessGeocodeQuestion (const string & name, QuestionType q_type) 
{
	//cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	vector <ActiveVariableInfo* > av_info;
	PrintActiveVariablesAtScope(active_scope_list, av_info);
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();

	GeocodeGMapV3Question * geo_code_question = 0;
	if (qscript_parser::flagIsAForBody_) {
		//cerr << " GEOCODE_GMAPV3 within for loops not yet implemented - exiting"
		//	<< endl;
		//exit (1);
		geo_code_question = new GeocodeGMapV3Question (QUESTION_ARR_TYPE, line_no
				, nest_lev, flagIsAForBody_
				, name, ::text_expr_vec, q_type
				, qscript_parser::for_loop_max_counter_stack
				, cmpd_stmt_ptr
				, av_info, question_attributes);
		qscript_parser::delete_manually_in_cleanup.push_back(
			active_scope_list[0]->insert(name.c_str(), QUESTION_ARR_TYPE, geo_code_question));
	} else {
		geo_code_question = new GeocodeGMapV3Question (QUESTION_TYPE, line_no
						, nest_lev, flagIsAForBody_
						, name, ::text_expr_vec, q_type
						, cmpd_stmt_ptr
						, av_info, question_attributes);
		qscript_parser::delete_manually_in_cleanup.push_back(
				active_scope_list[0]->insert(name.c_str(), QUESTION_TYPE, geo_code_question));
	}
	question_list.push_back(geo_code_question);
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	if (flag_next_question_start_of_block) {
		geo_code_question->isStartOfBlock_ = true;
		flag_next_question_start_of_block = false;
	}
	//cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
	return geo_code_question;
}



	void do_stub_pair_checks (const string & stub_text, int code, const stub_pair_options & current_stub_pair_options)
	{
		using qscript_parser::stub_list;
		string s1=stub_text;
		//int32_t code=$2;
		struct stub_pair pair1(s1, code, current_stub_pair_options);
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


// Close namespace
}


