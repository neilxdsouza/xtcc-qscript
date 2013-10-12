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
#define YYLAST   882

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNRULES -- Number of states.  */
#define YYNSTATES  368

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
     110,   112,   114,   116,   118,   121,   122,   133,   137,   138,
     143,   144,   152,   157,   159,   165,   173,   176,   180,   186,
     195,   206,   214,   220,   226,   234,   243,   251,   253,   257,
     259,   264,   271,   282,   284,   285,   288,   290,   293,   295,
     297,   301,   305,   309,   313,   317,   320,   324,   328,   332,
     336,   340,   344,   348,   352,   356,   359,   361,   363,   365,
     370,   375,   377,   381,   385,   390,   394,   401,   406,   411,
     413,   417,   419,   424,   429,   431,   435,   439,   441,   445,
     447,   451,   455,   457,   458,   465,   471,   473,   477,   479,
     482,   485,   489,   497,   508,   518,   532,   545,   553,   564,
     575,   583,   591,   597,   603,   604,   613,   614,   621,   623,
     626
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
      67,    -1,    80,    79,     5,    38,   103,    67,    -1,    79,
       5,    38,   103,    67,    -1,    79,     5,    34,   103,    35,
      67,    -1,    97,    -1,    92,    -1,    81,    -1,   111,    -1,
     113,    -1,    85,    -1,    91,    -1,    83,    -1,   117,    -1,
      93,    -1,    94,    -1,    95,    -1,   120,    -1,   123,    -1,
     118,    -1,    96,    -1,    86,    -1,    89,    -1,     1,    67,
      -1,    -1,    18,    36,   103,    67,   103,    67,   103,    37,
      84,    85,    -1,    90,    78,    68,    -1,    -1,    31,     5,
      87,    85,    -1,    -1,    31,     5,    88,    32,    38,     3,
      85,    -1,     5,    69,    33,    67,    -1,    70,    -1,    58,
      36,   103,    37,    82,    -1,    58,    36,   103,    37,    82,
      59,    82,    -1,   103,    67,    -1,    19,     5,    67,    -1,
      23,    36,     5,    37,    67,    -1,    23,    36,     5,    34,
     103,    35,    37,    67,    -1,    23,    36,     5,    34,   103,
      35,    40,     7,    37,    67,    -1,    23,    36,     5,    40,
       7,    37,    67,    -1,    24,    36,   103,    37,    67,    -1,
      26,    36,   103,    37,    67,    -1,     5,    98,   105,    79,
     108,   100,    67,    -1,     5,    98,   105,    79,   108,   106,
     100,    67,    -1,     5,    98,   105,    79,     5,   100,    67,
      -1,    99,    -1,    98,    71,    99,    -1,     7,    -1,     5,
      34,   103,    35,    -1,     5,    69,    60,    34,   103,    35,
      -1,    71,     5,    34,   103,    35,    69,    60,    34,   103,
      35,    -1,     5,    -1,    -1,    71,   101,    -1,   102,    -1,
     101,   102,    -1,    20,    -1,    21,    -1,   103,    50,   103,
      -1,   103,    49,   103,    -1,   103,    51,   103,    -1,   103,
      52,   103,    -1,   103,    53,   103,    -1,    49,   103,    -1,
     103,    45,   103,    -1,   103,    46,   103,    -1,   103,    48,
     103,    -1,   103,    47,   103,    -1,   103,    44,   103,    -1,
     103,    43,   103,    -1,   103,    41,   103,    -1,   103,    42,
     103,    -1,   103,    38,   103,    -1,    54,   103,    -1,     3,
      -1,     4,    -1,     5,    -1,     5,    34,   103,    35,    -1,
       5,    36,   104,    37,    -1,     7,    -1,    36,   103,    37,
      -1,   103,    17,   108,    -1,     6,    36,     5,    37,    -1,
     103,    17,     5,    -1,   103,    17,     5,    34,   103,    35,
      -1,    25,    36,     5,    37,    -1,    56,    36,     5,    37,
      -1,   103,    -1,   104,    40,   103,    -1,     8,    -1,     9,
      36,     3,    37,    -1,    22,    36,   107,    37,    -1,   106,
      -1,   107,    40,   106,    -1,     3,    49,     3,    -1,     3,
      -1,    36,   109,    37,    -1,   110,    -1,   109,    40,   110,
      -1,     3,    49,     3,    -1,     3,    -1,    -1,    60,     5,
     112,    38,   115,    67,    -1,    61,     5,    38,   114,    67,
      -1,     7,    -1,   114,    40,     7,    -1,   116,    -1,   115,
     116,    -1,     7,     3,    -1,     7,     3,    22,    -1,    62,
      36,     5,    40,     5,    37,    67,    -1,    62,    36,     5,
      40,     5,    34,   103,    35,    37,    67,    -1,    63,    36,
       5,    40,    36,     5,    37,    37,    67,    -1,    63,    36,
       5,    34,   103,    35,    40,     5,    34,   103,    35,    37,
      67,    -1,    63,    36,     5,    34,   103,    35,    40,    36,
       5,    37,    37,    67,    -1,    63,    36,     5,    40,     5,
      37,    67,    -1,    63,    36,     5,    40,     5,    34,   103,
      35,    37,    67,    -1,    63,    36,     5,    34,   103,    35,
      40,   108,    37,    67,    -1,    63,    36,     5,    40,   108,
      37,    67,    -1,    62,    36,     5,    40,   108,    37,    67,
      -1,    64,    36,     5,    37,    67,    -1,    65,    36,     5,
      37,    67,    -1,    -1,    28,   122,   119,    29,   122,    71,
       3,    67,    -1,    -1,    27,   122,   121,    29,   122,    67,
      -1,     5,    -1,   122,     5,    -1,    30,     5,    67,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   177,   177,   185,   191,   191,   226,   230,   236,   243,
     252,   261,   269,   278,   286,   287,   288,   289,   290,   291,
     292,   295,   300,   303,   305,   308,   318,   319,   320,   321,
     322,   323,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   358,   358,   378,   383,   383,
     397,   397,   414,   442,   452,   471,   512,   533,   540,   546,
     552,   557,   565,   572,   580,   594,   607,   619,   620,   623,
     626,   645,   668,   691,   715,   716,   720,   721,   724,   727,
     733,   742,   751,   760,   769,   778,   787,   796,   805,   814,
     823,   832,   841,   850,   859,   868,   877,   886,   894,   902,
     910,   964,   971,   978,   987,   993,   999,  1005,  1011,  1029,
    1030,  1035,  1041,  1046,  1051,  1052,  1056,  1067,  1073,  1077,
    1078,  1081,  1093,  1099,  1099,  1145,  1159,  1162,  1169,  1170,
    1173,  1203,  1237,  1241,  1267,  1273,  1279,  1293,  1297,  1302,
    1308,  1314,  1321,  1324,  1329,  1329,  1353,  1353,  1376,  1377,
    1381
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
  "page_stmt", "$@3", "$@4", "randomize_stmt", "open_curly", "if_stmt",
  "expr_stmt", "goto_stmt", "clear_stmt", "column_stmt", "newcard_stmt",
  "question", "text_expr_list", "text_expr", "attribute_list",
  "attributes", "attribute", "expression", "expr_list", "qtype",
  "mutex_range", "mutex_range_list", "range_allowed_values", "range_list",
  "range", "stubs", "$@5", "named_attributes", "named_attribute_list",
  "stub_list", "stub", "stub_manip_stmts", "brand_rank_recode_stmt", "$@6",
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
      82,    82,    82,    82,    82,    84,    83,    85,    87,    86,
      88,    86,    89,    90,    91,    91,    92,    93,    94,    94,
      94,    94,    95,    96,    97,    97,    97,    98,    98,    99,
      99,    99,    99,    99,   100,   100,   101,   101,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   104,
     104,   105,   105,   106,   107,   107,   106,   106,   108,   109,
     109,   110,   110,   112,   111,   113,   114,   114,   115,   115,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   119,   118,   121,   120,   122,   122,
     123
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     7,     1,     3,     2,     5,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     6,     5,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0,    10,     3,     0,     4,
       0,     7,     4,     1,     5,     7,     2,     3,     5,     8,
      10,     7,     5,     5,     7,     8,     7,     1,     3,     1,
       4,     6,    10,     1,     0,     2,     1,     2,     1,     1,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     4,
       4,     1,     3,     3,     4,     3,     6,     4,     4,     1,
       3,     1,     4,     4,     1,     3,     3,     1,     3,     1,
       3,     3,     1,     0,     6,     5,     1,     3,     1,     2,
       2,     3,     7,    10,     9,    13,    12,     7,    10,    10,
       7,     7,     5,     5,     0,     8,     0,     6,     1,     2,
       3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    15,    16,    17,    18,    19,    20,     0,
       3,     0,    53,     2,     0,     1,     0,     0,    96,    97,
      98,     0,   101,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    12,
      33,    31,    42,    43,    32,    27,    35,    36,    37,    41,
      26,     0,    29,    30,    34,    40,    38,    39,    11,    44,
      73,    69,     0,     0,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,   148,   146,   144,     0,    48,
      98,     0,    85,    95,     0,     0,   123,     0,     0,     0,
       0,     0,    47,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,     0,     6,     0,     0,     0,     0,   109,     0,
       0,     0,   111,     0,     0,     0,     0,     0,    57,     0,
       0,     0,     0,   149,     0,     0,   150,     0,     0,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,     0,   105,     0,   103,    94,    92,    93,    91,    90,
      86,    87,    89,    88,    81,    80,    82,    83,    84,     4,
      11,     8,     0,     0,     0,    99,   100,     0,    52,     0,
       0,    68,     0,   104,     0,     0,     0,     0,     0,   107,
       0,     0,     0,    49,     0,   108,     0,     0,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
       0,   119,     0,     7,     0,    10,    70,     0,   110,     0,
       0,    74,    74,     0,     0,    58,     0,    62,    63,     0,
       0,     0,    54,     0,     0,   128,     0,   125,     0,     0,
       0,     0,     0,     0,   142,   143,     0,    24,     0,     0,
       0,   118,     0,     5,     0,     0,     0,   112,     0,     0,
     117,     0,     0,    74,     0,     0,     0,   147,     0,     0,
       0,   130,   124,   129,   127,     0,     0,     0,     0,     0,
       0,     0,     0,    25,    23,   106,   121,   120,     9,    71,
       0,    78,    79,    75,    76,    66,     0,     0,    64,     0,
       0,     0,     0,    61,     0,    51,    55,   131,     0,   132,
     141,     0,     0,   137,     0,   140,     0,    77,   116,   114,
       0,    65,    45,    59,     0,   145,     0,     0,     0,     0,
       0,     0,     0,   113,     0,     0,     0,     0,     0,     0,
       0,     0,   134,     0,   115,    46,    60,   133,     0,     0,
     139,   138,    72,     0,     0,     0,   136,   135
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,   222,   122,   123,    45,    46,    47,    48,
      49,    50,   345,    51,    52,   147,   148,    53,    14,    54,
      55,    56,    57,    58,    59,    60,    76,    77,   269,   303,
     304,    61,   129,   135,   273,   330,   164,   220,   221,    62,
     152,    63,   209,   244,   245,    64,    65,   145,    66,   144,
      86,    67
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -297
static const yytype_int16 yypact[] =
{
      97,   -51,  -297,  -297,  -297,  -297,  -297,  -297,  -297,    43,
    -297,    50,  -297,  -297,   270,  -297,   -16,    -7,  -297,  -297,
       3,    68,  -297,    94,   135,   108,   112,   114,   115,   147,
     147,   148,   149,    93,  -297,    93,    93,   120,   123,   153,
     155,   125,   129,   144,   145,   200,   159,   177,  -297,  -297,
    -297,  -297,  -297,  -297,  -297,  -297,  -297,  -297,  -297,  -297,
    -297,   304,  -297,  -297,  -297,  -297,  -297,  -297,   177,  -297,
     -18,  -297,    93,    93,   143,   178,    21,  -297,   179,    93,
     127,   191,    93,   192,    93,  -297,   193,   193,   132,   168,
      25,   489,   185,   185,   203,    93,  -297,   171,   212,   215,
     217,   224,  -297,  -297,    67,   227,     9,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,  -297,   -19,  -297,     7,    93,   173,   508,   811,    -4,
     167,   201,  -297,   202,    19,   177,   204,   341,  -297,    82,
     527,   206,   545,  -297,   208,   216,  -297,   -51,   214,  -297,
     207,   564,   209,   241,   210,    81,   218,   222,    93,    93,
    -297,   213,   232,   249,  -297,   811,   829,   353,   122,   122,
      15,    15,    15,    15,     5,     5,   185,   185,   185,  -297,
     177,   233,   264,   583,   238,  -297,  -297,    93,  -297,    93,
     276,  -297,    10,  -297,    93,    93,   220,   283,   225,  -297,
     235,   147,   147,  -297,   253,  -297,   270,   292,  -297,   -23,
      26,    93,    33,   236,   237,   602,   378,    93,    93,   256,
      66,  -297,   -51,  -297,   305,  -297,  -297,    93,   811,   621,
     274,   242,    20,   415,   640,  -297,   275,  -297,  -297,     4,
      23,   311,   248,   312,    28,  -297,   310,  -297,    80,   281,
     659,    91,   128,   285,  -297,  -297,   258,  -297,   452,   678,
     317,  -297,   249,  -297,   288,   697,   260,  -297,   103,   269,
     278,   301,   271,   242,    93,    95,   272,  -297,   338,   -51,
     270,   321,  -297,  -297,  -297,    93,   293,   294,   319,    93,
     295,   326,   297,  -297,  -297,  -297,  -297,  -297,  -297,  -297,
     306,  -297,  -297,   103,  -297,  -297,   362,    31,  -297,   300,
     716,   302,   361,  -297,   307,  -297,  -297,  -297,   735,  -297,
    -297,    84,   754,  -297,   335,  -297,   339,  -297,  -297,  -297,
     101,  -297,  -297,  -297,   340,  -297,   343,   342,   140,   344,
     370,   308,    93,  -297,    31,   -51,   345,   346,    93,   372,
     347,   348,  -297,   773,  -297,  -297,  -297,  -297,   792,   373,
    -297,  -297,  -297,   374,   350,   351,  -297,  -297
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -297,  -297,  -297,  -297,  -297,   198,  -297,     2,  -297,  -297,
     -40,  -297,  -297,    -1,  -297,  -297,  -297,  -297,  -297,  -297,
    -297,  -297,  -297,  -297,  -297,  -297,  -297,   299,  -219,  -297,
     131,   -32,  -297,  -297,  -296,  -297,  -185,  -297,   174,  -297,
    -297,  -297,  -297,  -297,   194,  -297,  -297,  -297,  -297,  -297,
     -24,  -297
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -51
static const yytype_int16 yytable[] =
{
      13,    91,    11,    92,    93,   103,    87,   232,    70,   143,
      71,   329,   181,   272,   162,   231,   125,   246,   179,    12,
      68,   180,   106,   270,    70,   249,    71,   253,   143,   132,
     133,   248,   106,   186,   270,   243,   187,    72,   251,    73,
     127,   128,   271,    15,   247,   163,   163,   137,   354,   105,
     140,   126,   142,   271,   309,    16,   118,   119,   120,    72,
      69,    73,   163,   151,   116,   117,   118,   119,   120,   252,
     124,   277,    74,   182,    75,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   337,
      75,   268,   134,   183,   278,   282,    18,    19,    90,    21,
      22,   158,     1,   261,    78,   159,   262,     2,     3,     4,
       5,     6,     7,     8,   285,   211,   195,   286,    27,   196,
     338,   212,   197,   301,   302,   289,   215,   216,   290,    33,
      79,   219,   311,   291,   160,   312,   339,   192,   343,   106,
      80,   344,    35,   219,    81,   349,   203,    36,    82,    37,
      83,    84,    85,    88,    89,   228,    94,   229,    96,    95,
      97,    98,   233,   234,   104,    99,   242,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   130,   239,   240,   250,
     100,   101,   124,   131,   136,   258,   259,     2,     3,     4,
       5,     6,     7,     8,   138,   265,   139,   141,   143,   146,
     -50,    17,   106,    18,    19,    20,    21,    22,   150,   153,
       2,     3,     4,     5,     6,     7,     8,   154,    23,    24,
     155,   263,   156,    25,    26,    27,    28,    29,    30,   157,
      31,    32,   161,   184,   188,   189,    33,   201,   190,    34,
     316,   193,   310,   199,   205,   202,   204,   207,   208,    35,
     210,   217,   219,   318,    36,   213,    37,   322,    38,   214,
      39,    40,    41,    42,    43,    44,   218,   224,   102,   225,
      12,    17,   227,    18,    19,    20,    21,    22,   315,   230,
       2,     3,     4,     5,     6,     7,     8,   235,    23,    24,
     236,   241,   237,    25,    26,    27,    28,    29,    30,   243,
      31,    32,   238,   254,   255,   260,    33,   280,   264,    34,
     353,   267,   276,   268,   279,   281,   358,   284,   287,    35,
     296,   106,   292,   298,    36,   293,    37,   306,    38,   300,
      39,    40,    41,    42,    43,    44,   305,   307,   308,   313,
      12,   314,   107,   317,   355,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   106,   321,
     319,   320,   323,   324,   325,   328,   326,   331,   334,   333,
     106,   121,   341,   342,   335,   352,   348,   346,   223,   107,
     347,   350,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   106,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   351,   194,   359,
     364,   365,   356,   357,   360,   361,   107,   366,   367,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   106,   191,   327,     0,   297,     0,   283,     0,
       0,     0,     0,     0,     0,   257,     0,     0,     0,     0,
       0,     0,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   274,     0,     0,     0,     0,     0,     0,     0,
     107,     0,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   106,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   294,
       0,     0,     0,     0,     0,   106,   149,   107,     0,     0,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   185,   106,     0,   107,     0,     0,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   106,     0,   198,   107,     0,     0,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   106,   200,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     106,   206,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   226,   106,
       0,   107,     0,     0,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   256,   106,     0,
     107,     0,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   266,   106,     0,   107,
       0,     0,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   275,   106,     0,   107,     0,
       0,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   288,   106,     0,   107,     0,     0,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   295,   106,     0,   107,     0,     0,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   299,   106,     0,   107,     0,     0,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,     0,   106,   332,   107,     0,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     336,   106,     0,   107,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   340,
     106,     0,   107,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   362,   106,
       0,   107,     0,     0,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   363,   106,     0,
     107,     0,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   106,     0,     0,   107,
       0,     0,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,     0,     0,     0,     0,     0,
       0,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-297))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    33,     0,    35,    36,    45,    30,   192,     5,     5,
       7,   307,     5,   232,     5,     5,    34,    40,    37,    70,
      36,    40,    17,     3,     5,   210,     7,   212,     5,     8,
       9,     5,    17,    37,     3,     7,    40,    34,     5,    36,
      72,    73,    22,     0,    67,    36,    36,    79,   344,    47,
      82,    69,    84,    22,   273,     5,    51,    52,    53,    34,
      67,    36,    36,    95,    49,    50,    51,    52,    53,    36,
      68,    67,    69,    66,    71,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,     5,
      71,    71,    71,   125,    71,    67,     3,     4,     5,     6,
       7,    34,     5,    37,    36,    38,    40,    10,    11,    12,
      13,    14,    15,    16,    34,    34,    34,    37,    25,    37,
      36,    40,    40,    20,    21,    34,   158,   159,    37,    36,
      36,     3,    37,     5,    67,    40,   321,   135,    37,    17,
       5,    40,    49,     3,    36,     5,   147,    54,    36,    56,
      36,    36,     5,     5,     5,   187,    36,   189,     5,    36,
       5,    36,   194,   195,     5,    36,   206,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    33,   201,   202,   211,
      36,    36,   180,     5,     5,   217,   218,    10,    11,    12,
      13,    14,    15,    16,    67,   227,     5,     5,     5,    67,
      32,     1,    17,     3,     4,     5,     6,     7,     5,    38,
      10,    11,    12,    13,    14,    15,    16,     5,    18,    19,
       5,   222,     5,    23,    24,    25,    26,    27,    28,     5,
      30,    31,     5,    60,    67,    34,    36,    29,    36,    39,
     280,    37,   274,    37,    37,    29,    32,    38,     7,    49,
      40,    38,     3,   285,    54,    37,    56,   289,    58,    37,
      60,    61,    62,    63,    64,    65,    34,    34,    68,     5,
      70,     1,    34,     3,     4,     5,     6,     7,   279,     3,
      10,    11,    12,    13,    14,    15,    16,    67,    18,    19,
       7,    38,    67,    23,    24,    25,    26,    27,    28,     7,
      30,    31,    67,    67,    67,    49,    36,    59,     3,    39,
     342,    37,    37,    71,     3,     3,   348,     7,    37,    49,
       3,    17,    37,    35,    54,    67,    56,    49,    58,    69,
      60,    61,    62,    63,    64,    65,    67,    36,    67,    67,
      70,     3,    38,    22,   345,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    17,    40,
      67,    67,    67,    37,    67,     3,    60,    67,     7,    67,
      17,    67,    37,    34,    67,    67,    34,    37,   180,    38,
      37,    37,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    17,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    37,    67,    37,
      37,    37,    67,    67,    67,    67,    38,    67,    67,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    17,   134,   303,    -1,   262,    -1,   244,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      48,    49,    50,    51,    52,    53,    17,    -1,    -1,    38,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    10,    11,    12,    13,    14,    15,    16,    73,
      74,    79,    70,    85,    90,     0,     5,     1,     3,     4,
       5,     6,     7,    18,    19,    23,    24,    25,    26,    27,
      28,    30,    31,    36,    39,    49,    54,    56,    58,    60,
      61,    62,    63,    64,    65,    78,    79,    80,    81,    82,
      83,    85,    86,    89,    91,    92,    93,    94,    95,    96,
      97,   103,   111,   113,   117,   118,   120,   123,    36,    67,
       5,     7,    34,    36,    69,    71,    98,    99,    36,    36,
       5,    36,    36,    36,    36,     5,   122,   122,     5,     5,
       5,   103,   103,   103,    36,    36,     5,     5,    36,    36,
      36,    36,    68,    82,     5,    79,    17,    38,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    67,    76,    77,    79,    34,    69,   103,   103,   104,
      33,     5,     8,     9,    71,   105,     5,   103,    67,     5,
     103,     5,   103,     5,   121,   119,    67,    87,    88,    37,
       5,   103,   112,    38,     5,     5,     5,     5,    34,    38,
      67,     5,     5,    36,   108,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,    37,
      40,     5,    66,   103,    60,    35,    37,    40,    67,    34,
      36,    99,    79,    37,    67,    34,    37,    40,    37,    37,
      37,    29,    29,    85,    32,    37,    37,    38,     7,   114,
      40,    34,    40,    37,    37,   103,   103,    38,    34,     3,
     109,   110,    75,    77,    34,     5,    35,    34,   103,   103,
       3,     5,   108,   103,   103,    67,     7,    67,    67,   122,
     122,    38,    82,     7,   115,   116,    40,    67,     5,   108,
     103,     5,    36,   108,    67,    67,    35,    67,   103,   103,
      49,    37,    40,    85,     3,   103,    35,    37,    71,   100,
       3,    22,   100,   106,    67,    35,    37,    67,    71,     3,
      59,     3,    67,   116,     7,    34,    37,    37,    35,    34,
      37,     5,    37,    67,    67,    35,     3,   110,    35,    35,
      69,    20,    21,   101,   102,    67,    49,    36,    67,   100,
     103,    37,    40,    67,     3,    85,    82,    22,   103,    67,
      67,    40,   103,    67,    37,    67,    60,   102,     3,   106,
     107,    67,    37,    67,     7,    67,    35,     5,    36,   108,
      35,    37,    34,    37,    40,    84,    37,    37,    34,     5,
      37,    37,    67,   103,   106,    85,    67,    67,   103,    37,
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
#line 177 "src/q.ypp"
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
#line 185 "src/q.ypp"
    {
		(yyval.stmt)=(yyvsp[(1) - (1)].stmt);
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 191 "src/q.ypp"
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
#line 202 "src/q.ypp"
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
#line 226 "src/q.ypp"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 230 "src/q.ypp"
    {
		(yyval.v_list)=qscript_parser::link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 236 "src/q.ypp"
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
#line 243 "src/q.ypp"
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
#line 252 "src/q.ypp"
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
#line 261 "src/q.ypp"
    {
		(yyval.v_list)=0;
		}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 269 "src/q.ypp"
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
#line 278 "src/q.ypp"
    {
		(yyvsp[(1) - (2)].stmt) -> next_ = (yyvsp[(2) - (2)].stmt);
		(yyvsp[(2) - (2)].stmt) -> prev_ = (yyvsp[(1) - (2)].stmt);
		(yyval.stmt) = (yyvsp[(2) - (2)].stmt);
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 295 "src/q.ypp"
    {
		   (yyval.type_qual) = CONST_QUAL;
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 300 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 303 "src/q.ypp"
    {
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 305 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 308 "src/q.ypp"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].expr)/*, line_no*/);
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 323 "src/q.ypp"
    {
		(yyval.stmt) = (yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 338 "src/q.ypp"
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
#line 358 "src/q.ypp"
    {
		++qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.push_back ((yyvsp[(5) - (8)].expr));
	        qscript_parser::ParseSpecialCaseAndAttachMaxBounds ((yyvsp[(5) - (8)].expr));
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 362 "src/q.ypp"
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
#line 378 "src/q.ypp"
    {
		(yyval.c_stmt) = qscript_parser::ProcessCompoundStatement((yyvsp[(1) - (3)].c_stmt), (yyvsp[(2) - (3)].stmt));
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 383 "src/q.ypp"
    {qscript_parser::globalActivePageName_ = (yyvsp[(2) - (2)].name); cout << "globalActivePageName_: " << qscript_parser::globalActivePageName_ << endl; }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 383 "src/q.ypp"
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

  case 50:

/* Line 1806 of yacc.c  */
#line 397 "src/q.ypp"
    {qscript_parser::globalActivePageName_ = (yyvsp[(2) - (2)].name);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 397 "src/q.ypp"
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

  case 52:

/* Line 1806 of yacc.c  */
#line 414 "src/q.ypp"
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

  case 53:

/* Line 1806 of yacc.c  */
#line 442 "src/q.ypp"
    {
		CompoundStatement * cmpdStmt = qscript_parser::ProcessOpenCurly();
		//qscript_parser::compound_body_stack.push_back(cmpdStmt);
		//cmpdStmt->nestedCompoundStatementStack_=qscript_parser::compound_body_stack;
		(yyval.c_stmt)=cmpdStmt;
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 452 "src/q.ypp"
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
#line 471 "src/q.ypp"
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
#line 513 "src/q.ypp"
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
#line 533 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new GotoStatement(GOTO_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(2) - (3)].name));
		// free($2); ? is this required here
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 540 "src/q.ypp"
    {
		// free($3); ? is this required here
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].name));
	}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 546 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (8)].name), (yyvsp[(5) - (8)].expr));
		// free($3); ? is this required here
	}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 552 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (10)].name), (yyvsp[(5) - (10)].expr), (yyvsp[(8) - (10)].text_buf));
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 557 "src/q.ypp"
    {
		// free($3); ? is this required here
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ClearStatement(CLEAR_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (7)].name), (yyvsp[(5) - (7)].text_buf));
	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 565 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ColumnStatement(COLUMN_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr));
	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 572 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new NewCardStatement(COLUMN_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr));
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 580 "src/q.ypp"
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

  case 65:

/* Line 1806 of yacc.c  */
#line 594 "src/q.ypp"
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

  case 66:

/* Line 1806 of yacc.c  */
#line 607 "src/q.ypp"
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

  case 69:

/* Line 1806 of yacc.c  */
#line 623 "src/q.ypp"
    {
		text_expr_vec.push_back (new TextExpression(string((yyvsp[(1) - (1)].text_buf))));
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 626 "src/q.ypp"
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

  case 71:

/* Line 1806 of yacc.c  */
#line 645 "src/q.ypp"
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

  case 72:

/* Line 1806 of yacc.c  */
#line 668 "src/q.ypp"
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

  case 73:

/* Line 1806 of yacc.c  */
#line 691 "src/q.ypp"
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

  case 78:

/* Line 1806 of yacc.c  */
#line 724 "src/q.ypp"
    {
		question_attributes.setHidden();
	}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 727 "src/q.ypp"
    {
		question_attributes.setAllowBlank();
	}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 733 "src/q.ypp"
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

  case 81:

/* Line 1806 of yacc.c  */
#line 742 "src/q.ypp"
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

  case 82:

/* Line 1806 of yacc.c  */
#line 751 "src/q.ypp"
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

  case 83:

/* Line 1806 of yacc.c  */
#line 760 "src/q.ypp"
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

  case 84:

/* Line 1806 of yacc.c  */
#line 769 "src/q.ypp"
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

  case 85:

/* Line 1806 of yacc.c  */
#line 778 "src/q.ypp"
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

  case 86:

/* Line 1806 of yacc.c  */
#line 787 "src/q.ypp"
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

  case 87:

/* Line 1806 of yacc.c  */
#line 796 "src/q.ypp"
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

  case 88:

/* Line 1806 of yacc.c  */
#line 805 "src/q.ypp"
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

  case 89:

/* Line 1806 of yacc.c  */
#line 814 "src/q.ypp"
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

  case 90:

/* Line 1806 of yacc.c  */
#line 823 "src/q.ypp"
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

  case 91:

/* Line 1806 of yacc.c  */
#line 832 "src/q.ypp"
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

  case 92:

/* Line 1806 of yacc.c  */
#line 841 "src/q.ypp"
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

  case 93:

/* Line 1806 of yacc.c  */
#line 850 "src/q.ypp"
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

  case 94:

/* Line 1806 of yacc.c  */
#line 859 "src/q.ypp"
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

  case 95:

/* Line 1806 of yacc.c  */
#line 868 "src/q.ypp"
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

  case 96:

/* Line 1806 of yacc.c  */
#line 877 "src/q.ypp"
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

  case 97:

/* Line 1806 of yacc.c  */
#line 886 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].dval));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 894 "src/q.ypp"
    {
		using qscript_parser::mem_addr;
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression((yyvsp[(1) - (1)].name), oper_name );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 902 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser::mem_addr;
		(yyval.expr) = new Unary2Expression(oper_arrderef, (yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].expr));
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 910 "src/q.ypp"
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

  case 101:

/* Line 1806 of yacc.c  */
#line 964 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new Unary2Expression(strdup((yyvsp[(1) - (1)].text_buf)), oper_text_expr);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 971 "src/q.ypp"
    {
		using qscript_parser::line_no;
		(yyval.expr) = new UnaryExpression((yyvsp[(2) - (3)].expr), oper_parexp );
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, line_no);
		}
	}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 978 "src/q.ypp"
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

  case 104:

/* Line 1806 of yacc.c  */
#line 987 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression((yyvsp[(3) - (4)].name), oper_to_string);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 993 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].name), 0, oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 999 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (6)].expr), (yyvsp[(3) - (6)].name), (yyvsp[(5) - (6)].expr), oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1005 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_isanswered);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1011 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_count);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1029 "src/q.ypp"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1030 "src/q.ypp"
    {
		(yyval.expr)=qscript_parser::link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1035 "src/q.ypp"
    { 
	       qscript_parser::q_type = spn; 
	       // we need this =1 when generating
	       // code for flat file creation
		qscript_parser::no_mpn = 1;
       }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1041 "src/q.ypp"
    { qscript_parser::q_type = mpn;
		qscript_parser::no_mpn = (yyvsp[(3) - (4)].ival);
	}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1046 "src/q.ypp"
    { 
		     qscript_parser::has_mutex_range = true;
	     }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1056 "src/q.ypp"
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

  case 117:

/* Line 1806 of yacc.c  */
#line 1067 "src/q.ypp"
    {
		qscript_parser::mutex_range_set.add_indiv((yyvsp[(1) - (1)].ival));
	}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1073 "src/q.ypp"
    { }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1081 "src/q.ypp"
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

  case 122:

/* Line 1806 of yacc.c  */
#line 1093 "src/q.ypp"
    {
		//qscript_parser::xs.indiv.insert($1);
		qscript_parser::xs.add_indiv((yyvsp[(1) - (1)].ival));
	}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1099 "src/q.ypp"
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

  case 124:

/* Line 1806 of yacc.c  */
#line 1120 "src/q.ypp"
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

  case 125:

/* Line 1806 of yacc.c  */
#line 1145 "src/q.ypp"
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

  case 126:

/* Line 1806 of yacc.c  */
#line 1159 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(1) - (1)].text_buf));
	}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1162 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(3) - (3)].text_buf));
	}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1173 "src/q.ypp"
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

  case 131:

/* Line 1806 of yacc.c  */
#line 1203 "src/q.ypp"
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

  case 132:

/* Line 1806 of yacc.c  */
#line 1237 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), 0, (yyvsp[(5) - (7)].name), 0);
	}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1241 "src/q.ypp"
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

  case 134:

/* Line 1806 of yacc.c  */
#line 1267 "src/q.ypp"
    {
                // 2nd NAME is an expression
                Unary2Expression * un2e = new Unary2Expression ((yyvsp[(6) - (9)].name), oper_name);
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (9)].name), 0, un2e);
	}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1273 "src/q.ypp"
    {
		cout << __LINE__ << "|^: reached here" << endl;		
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (13)].name), (yyvsp[(5) - (13)].expr), (yyvsp[(8) - (13)].name), (yyvsp[(10) - (13)].expr));
        }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1279 "src/q.ypp"
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

  case 137:

/* Line 1806 of yacc.c  */
#line 1293 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), 0, (yyvsp[(5) - (7)].name), 0);
	}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1297 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), 0, (yyvsp[(5) - (10)].name), (yyvsp[(7) - (10)].expr));
		//cout << "reached here" << endl;		
	}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1302 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), (yyvsp[(5) - (10)].expr), xs);
		xs.reset();
        }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1308 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), 0, xs);
		xs.reset();
	}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1314 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), 0, xs);
		//using qscript_parser::xs;
		xs.reset();
	}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1321 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_UNSET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1324 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_SET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1329 "src/q.ypp"
    { recode_list = name_list; name_list.clear(); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1330 "src/q.ypp"
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

  case 146:

/* Line 1806 of yacc.c  */
#line 1353 "src/q.ypp"
    { recode_list = name_list; name_list.clear(); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1354 "src/q.ypp"
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

  case 148:

/* Line 1806 of yacc.c  */
#line 1376 "src/q.ypp"
    { name_list.push_back((yyvsp[(1) - (1)].name)); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1377 "src/q.ypp"
    { name_list.push_back((yyvsp[(2) - (2)].name)); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1381 "src/q.ypp"
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
#line 3629 "src/q.cpp"
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
#line 1394 "src/q.ypp"



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


