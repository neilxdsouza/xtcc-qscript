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
	vector<TextExpression*> text_expr_vec;
	vector<string> vec_named_attribute_list;
	vector<Unary2Expression*> clear_questions_list;
	stub_pair_options current_stub_pair_options;




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
     MUTEX = 284,
     OTHER = 285,
     CLEAR = 286,
     COLUMN = 287,
     ISANSWERED = 288,
     NEWCARD = 289,
     PAGE = 290,
     GRID_SIZE = 291,
     RANDOMIZE = 292,
     CONST = 293,
     LOGOR = 294,
     LOGAND = 295,
     NOEQ = 296,
     ISEQ = 297,
     GEQ = 298,
     LEQ = 299,
     NOT = 300,
     UMINUS = 301,
     COUNT = 302,
     FUNC_CALL = 303,
     IF = 304,
     ELSE = 305,
     STUBS_LIST = 306,
     NAMED_ATTRIBUTES = 307,
     SETDEL = 308,
     SETADD = 309,
     UNSET = 310,
     SETALL = 311
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
	struct Unary2Expression * ue2expr;



/* Line 293 of yacc.c  */
#line 230 "src/q.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 242 "src/q.cpp"

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
#define YYLAST   822

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNRULES -- Number of states.  */
#define YYNSTATES  357

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    57,    70,     2,
      40,    41,    55,    54,    44,    53,    73,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    75,    71,
      49,    42,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    76,    72,     2,     2,     2,     2,
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
      35,    36,    37,    43,    45,    46,    47,    48,    51,    52,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69
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
     110,   112,   115,   116,   127,   131,   136,   137,   142,   143,
     151,   153,   159,   167,   170,   174,   176,   180,   182,   187,
     195,   201,   207,   215,   224,   232,   238,   244,   250,   252,
     256,   258,   263,   270,   272,   273,   276,   278,   281,   283,
     285,   289,   293,   297,   301,   305,   308,   312,   316,   320,
     324,   328,   332,   336,   340,   344,   347,   349,   351,   353,
     358,   363,   365,   369,   373,   378,   382,   389,   394,   399,
     401,   405,   407,   412,   414,   416,   418,   420,   422,   424,
     429,   431,   435,   439,   441,   445,   447,   451,   455,   457,
     458,   465,   471,   473,   477,   479,   483,   485,   489,   491,
     493,   496,   499,   502,   505,   510,   518,   529,   539,   553,
     566,   574,   585,   596,   604,   612,   618
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      78,     0,    -1,     5,    90,    -1,    79,    -1,    -1,    84,
       5,    40,    81,    41,    80,    90,    -1,    82,    -1,    81,
      44,    82,    -1,    84,     5,    -1,    84,     5,    38,     3,
      39,    -1,    84,    70,     5,    -1,    -1,    87,    -1,    83,
      87,    -1,    17,    -1,    18,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    43,    -1,    84,     5,
      71,    -1,    85,    84,     5,    42,   110,    71,    -1,    84,
       5,    42,   110,    71,    -1,    84,     5,    38,   110,    39,
      71,    -1,   104,    -1,    97,    -1,    86,    -1,   118,    -1,
     120,    -1,    90,    -1,    96,    -1,    88,    -1,   126,    -1,
      98,    -1,   101,    -1,   102,    -1,   103,    -1,    92,    -1,
      91,    -1,     1,    71,    -1,    -1,    25,    40,   110,    71,
     110,    71,   110,    41,    89,    90,    -1,    95,    83,    72,
      -1,     5,    73,    37,    71,    -1,    -1,    35,     5,    93,
      90,    -1,    -1,    35,     5,    94,    36,    42,     3,    90,
      -1,    74,    -1,    62,    40,   110,    41,    87,    -1,    62,
      40,   110,    41,    87,    63,    87,    -1,   110,    71,    -1,
      26,     5,    71,    -1,   100,    -1,    99,    44,   100,    -1,
       5,    -1,     5,    38,   110,    39,    -1,    31,    40,    99,
      44,     7,    41,    71,    -1,    32,    40,   110,    41,    71,
      -1,    34,    40,   110,    41,    71,    -1,     5,   105,   112,
      84,   115,   107,    71,    -1,     5,   105,   112,    84,   115,
     113,   107,    71,    -1,     5,   105,   112,    84,     5,   107,
      71,    -1,     5,   105,   112,     7,    71,    -1,     5,   105,
     112,   107,    71,    -1,     5,   105,    13,   107,    71,    -1,
     106,    -1,   105,    75,   106,    -1,     7,    -1,     5,    38,
     110,    39,    -1,     5,    73,    64,    38,   110,    39,    -1,
       5,    -1,    -1,    75,   108,    -1,   109,    -1,   108,   109,
      -1,    27,    -1,    28,    -1,   110,    54,   110,    -1,   110,
      53,   110,    -1,   110,    55,   110,    -1,   110,    56,   110,
      -1,   110,    57,   110,    -1,    53,   110,    -1,   110,    49,
     110,    -1,   110,    50,   110,    -1,   110,    52,   110,    -1,
     110,    51,   110,    -1,   110,    48,   110,    -1,   110,    47,
     110,    -1,   110,    45,   110,    -1,   110,    46,   110,    -1,
     110,    42,   110,    -1,    58,   110,    -1,     3,    -1,     4,
      -1,     5,    -1,     5,    38,   110,    39,    -1,     5,    40,
     111,    41,    -1,     7,    -1,    40,   110,    41,    -1,   110,
      24,   115,    -1,     6,    40,     5,    41,    -1,   110,    24,
       5,    -1,   110,    24,     5,    38,   110,    39,    -1,    33,
      40,     5,    41,    -1,    60,    40,     5,    41,    -1,   110,
      -1,   111,    44,   110,    -1,     8,    -1,     9,    40,     3,
      41,    -1,    10,    -1,    12,    -1,    11,    -1,    14,    -1,
      16,    -1,    15,    -1,    29,    40,   114,    41,    -1,   113,
      -1,   114,    44,   113,    -1,     3,    53,     3,    -1,     3,
      -1,    40,   116,    41,    -1,   117,    -1,   116,    44,   117,
      -1,     3,    53,     3,    -1,     3,    -1,    -1,    64,     5,
     119,    42,   122,    71,    -1,    65,     5,    42,   121,    71,
      -1,     7,    -1,   121,    44,     7,    -1,   125,    -1,   122,
      44,   125,    -1,   124,    -1,   123,    76,   124,    -1,    29,
      -1,    30,    -1,    12,     7,    -1,    11,     7,    -1,    10,
       7,    -1,     7,     3,    -1,     7,     3,    75,   123,    -1,
      66,    40,     5,    44,     5,    41,    71,    -1,    66,    40,
       5,    44,     5,    38,   110,    39,    41,    71,    -1,    67,
      40,     5,    44,    40,     5,    41,    41,    71,    -1,    67,
      40,     5,    38,   110,    39,    44,     5,    38,   110,    39,
      41,    71,    -1,    67,    40,     5,    38,   110,    39,    44,
      40,     5,    41,    41,    71,    -1,    67,    40,     5,    44,
       5,    41,    71,    -1,    67,    40,     5,    44,     5,    38,
     110,    39,    41,    71,    -1,    67,    40,     5,    38,   110,
      39,    44,   115,    41,    71,    -1,    67,    40,     5,    44,
     115,    41,    71,    -1,    66,    40,     5,    44,   115,    41,
      71,    -1,    68,    40,     5,    41,    71,    -1,    69,    40,
       5,    41,    71,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   177,   177,   185,   191,   191,   227,   231,   237,   244,
     253,   262,   270,   279,   287,   288,   289,   290,   291,   292,
     293,   296,   301,   304,   306,   309,   319,   320,   321,   322,
     323,   324,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   356,   356,   375,   390,   418,   418,   436,   436,
     455,   469,   488,   528,   549,   556,   559,   564,   576,   604,
     613,   620,   628,   642,   655,   665,   671,   676,   686,   687,
     690,   693,   712,   735,   759,   760,   764,   765,   768,   771,
     777,   786,   795,   804,   813,   822,   831,   840,   849,   858,
     867,   876,   885,   894,   903,   912,   921,   930,   938,   946,
     954,  1008,  1015,  1022,  1031,  1037,  1043,  1049,  1055,  1073,
    1074,  1079,  1085,  1088,  1091,  1094,  1097,  1100,  1103,  1108,
    1113,  1114,  1118,  1129,  1135,  1139,  1140,  1143,  1155,  1161,
    1161,  1197,  1211,  1214,  1221,  1222,  1226,  1228,  1231,  1234,
    1237,  1241,  1246,  1252,  1285,  1361,  1365,  1384,  1390,  1395,
    1409,  1413,  1417,  1423,  1429,  1435,  1438
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
  "STRING_T", "IN", "FOR", "GOTO", "HIDDEN", "ALLOW_BLANK", "MUTEX",
  "OTHER", "CLEAR", "COLUMN", "ISANSWERED", "NEWCARD", "PAGE", "GRID_SIZE",
  "RANDOMIZE", "'['", "']'", "'('", "')'", "'='", "CONST", "','", "LOGOR",
  "LOGAND", "NOEQ", "ISEQ", "'<'", "'>'", "GEQ", "LEQ", "'-'", "'+'",
  "'*'", "'/'", "'%'", "NOT", "UMINUS", "COUNT", "FUNC_CALL", "IF", "ELSE",
  "STUBS_LIST", "NAMED_ATTRIBUTES", "SETDEL", "SETADD", "UNSET", "SETALL",
  "'&'", "';'", "'}'", "'.'", "'{'", "':'", "'|'", "$accept", "prog",
  "func_defn", "$@1", "decl_comma_list", "var_decl", "stmt_list",
  "datatype", "type_qual", "decl_stmt", "stmt", "for_loop_stmt", "$@2",
  "cmpd_stmt", "randomize_stmt", "page_stmt", "$@3", "$@4", "open_curly",
  "if_stmt", "expr_stmt", "goto_stmt", "question_expr_list",
  "question_expr", "clear_stmt", "column_stmt", "newcard_stmt", "question",
  "text_expr_list", "text_expr", "attribute_list", "attributes",
  "attribute", "expression", "expr_list", "qtype", "mutex_range",
  "mutex_range_list", "range_allowed_values", "range_list", "range",
  "stubs", "$@5", "named_attributes", "named_attribute_list", "stub_list",
  "stub_options_list", "stub_option", "stub", "stub_manip_stmts", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,    91,    93,
      40,    41,    61,   293,    44,   294,   295,   296,   297,    60,
      62,   298,   299,    45,    43,    42,    47,    37,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
      38,    59,   125,    46,   123,    58,   124
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    78,    80,    79,    81,    81,    82,    82,
      82,    82,    83,    83,    84,    84,    84,    84,    84,    84,
      84,    85,    86,    86,    86,    86,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    89,    88,    90,    91,    93,    92,    94,    92,
      95,    96,    96,    97,    98,    99,    99,   100,   100,   101,
     102,   103,   104,   104,   104,   104,   104,   104,   105,   105,
     106,   106,   106,   106,   107,   107,   108,   108,   109,   109,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   111,
     111,   112,   112,   112,   112,   112,   112,   112,   112,   113,
     114,   114,   113,   113,   115,   116,   116,   117,   117,   119,
     118,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     124,   124,   124,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     7,     1,     3,     2,     5,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     6,     5,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     0,    10,     3,     4,     0,     4,     0,     7,
       1,     5,     7,     2,     3,     1,     3,     1,     4,     7,
       5,     5,     7,     8,     7,     5,     5,     5,     1,     3,
       1,     4,     6,     1,     0,     2,     1,     2,     1,     1,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     4,
       4,     1,     3,     3,     4,     3,     6,     4,     4,     1,
       3,     1,     4,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     1,     3,     1,     3,     3,     1,     0,
       6,     5,     1,     3,     1,     3,     1,     3,     1,     1,
       2,     2,     2,     2,     4,     7,    10,     9,    13,    12,
       7,    10,    10,     7,     7,     5,     5
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    15,    16,    17,    18,    19,    20,     0,
       3,     0,    50,     2,     0,     1,     0,     0,    96,    97,
      98,     0,   101,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    12,    33,    31,    40,
      39,    32,    27,    35,    36,    37,    38,    26,     0,    29,
      30,    34,    11,    41,    73,    70,     0,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,     0,    46,    98,
       0,    85,    95,     0,     0,   129,     0,     0,     0,     0,
       0,    44,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      53,     0,     6,     0,     0,     0,     0,   109,     0,     0,
     111,     0,   113,   115,   114,    74,   116,   118,   117,     0,
      74,     0,     0,    54,    57,     0,    55,     0,     0,     0,
       0,     0,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,     0,   105,     0,   103,    94,    92,
      93,    91,    90,    86,    87,    89,    88,    81,    80,    82,
      83,    84,     4,    11,     8,     0,     0,     0,    99,   100,
       0,    45,     0,     0,     0,    69,     0,     0,     0,   104,
       0,     0,     0,     0,   107,     0,    47,     0,   108,     0,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   128,     0,   125,     0,     7,     0,    10,    71,
       0,   110,     0,    78,    79,    75,    76,    67,    65,    74,
      74,    66,     0,     0,     0,    56,    60,    61,     0,    51,
       0,     0,   134,     0,   131,     0,     0,     0,     0,     0,
       0,   155,   156,     0,    24,     0,     0,     0,   124,     0,
       5,     0,     0,   112,    77,     0,   123,     0,     0,    74,
       0,    58,     0,     0,     0,   143,     0,   130,   133,     0,
       0,     0,     0,     0,     0,     0,     0,    25,    23,   106,
     127,   126,     9,    72,    64,     0,     0,    62,     0,     0,
      59,    49,    52,     0,   135,     0,   145,   154,     0,     0,
     150,     0,   153,   122,   120,     0,    63,    42,     0,     0,
       0,   138,   139,   144,   136,     0,     0,     0,     0,     0,
       0,   119,     0,     0,   142,   141,   140,     0,     0,     0,
       0,     0,     0,   147,   121,    43,   137,   146,     0,     0,
     152,   151,     0,     0,     0,   149,   148
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,   215,   111,   112,    42,    43,    44,    45,
      46,    47,   333,    48,    49,    50,   140,   141,    14,    51,
      52,    53,   135,   136,    54,    55,    56,    57,    69,    70,
     184,   225,   226,    58,   118,   130,   269,   315,   157,   213,
     214,    59,   145,    60,   202,   241,   323,   324,   242,    61
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -289
static const yytype_int16 yypact[] =
{
     166,   -54,  -289,  -289,  -289,  -289,  -289,  -289,  -289,    50,
    -289,    48,  -289,  -289,   302,  -289,    58,    31,  -289,  -289,
      11,    66,  -289,    67,   115,    76,    85,    86,   101,   137,
     105,  -289,   105,   105,   108,   117,   155,   159,   133,   138,
     140,   173,   226,   210,   189,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,   148,  -289,
    -289,  -289,   189,  -289,   -31,  -289,   105,   105,   179,    78,
    -289,   212,   105,   147,   215,   105,   216,   105,   186,   -27,
     468,   199,   199,   219,   105,  -289,   183,   221,   223,   230,
     231,  -289,  -289,    75,   232,    12,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
    -289,    13,  -289,    27,   105,   175,   487,   746,    80,   167,
    -289,   200,  -289,  -289,  -289,   178,  -289,  -289,  -289,    40,
       8,   201,   332,  -289,   217,   218,  -289,   504,   222,   523,
     -54,   220,  -289,   224,   542,   225,   257,   227,    -4,   229,
     233,   105,   105,  -289,   234,   235,   265,  -289,   746,   765,
     378,    79,    79,   113,   113,   113,   113,     9,     9,   199,
     199,   199,  -289,   189,   237,   272,   561,   240,  -289,  -289,
     105,  -289,   277,    87,   211,  -289,   214,    16,   228,  -289,
     105,   105,   149,   241,  -289,   242,  -289,   239,  -289,   302,
     276,  -289,   -32,    18,   105,    55,   243,   244,   580,   366,
     105,   105,   236,    99,  -289,   -54,  -289,   284,  -289,  -289,
     105,   746,   255,  -289,  -289,    87,  -289,  -289,  -289,   178,
       7,  -289,   400,   599,   256,  -289,  -289,  -289,   298,   248,
     299,   -30,  -289,   297,  -289,    21,   275,   618,   109,   171,
     285,  -289,  -289,   246,  -289,   434,   637,   315,  -289,   265,
    -289,   290,   656,  -289,  -289,   259,   278,   300,   267,   178,
     105,  -289,   268,   -54,   302,   266,   276,  -289,  -289,   105,
     273,   279,   303,   105,   280,   305,   281,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,   340,     6,  -289,   282,   673,
    -289,  -289,  -289,    89,  -289,   692,  -289,  -289,    56,   711,
    -289,   307,  -289,  -289,  -289,   111,  -289,  -289,   342,   347,
     350,  -289,  -289,   283,  -289,   317,   323,   174,   322,   324,
     301,  -289,     6,   -54,  -289,  -289,  -289,    89,   304,   105,
     351,   320,   325,  -289,  -289,  -289,  -289,  -289,   730,   352,
    -289,  -289,   353,   326,   327,  -289,  -289
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -289,  -289,  -289,  -289,  -289,   263,  -289,    19,  -289,  -289,
     -40,  -289,  -289,    -1,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,   181,  -289,  -289,  -289,  -289,  -289,   270,
    -125,  -289,   170,   -29,  -289,  -289,  -288,  -289,  -181,  -289,
     141,  -289,  -289,  -289,  -289,  -289,  -289,    64,   128,  -289
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -49
static const yytype_int16 yytable[] =
{
      13,    80,    92,    81,    82,   188,   230,   114,   314,   266,
     266,    66,   243,    67,   276,   186,    64,   155,    65,    11,
      12,   229,   246,   245,   250,     2,     3,     4,     5,     6,
       7,     8,   174,    95,   204,   267,   267,   116,   117,   244,
     205,   277,   115,   132,   344,    64,   137,    65,   139,    66,
      15,    67,   156,    16,   172,   144,   156,   173,   156,   279,
     248,   326,   280,    94,   107,   108,   109,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   113,   183,   183,    68,   176,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   249,   327,   175,    62,   318,
     319,   320,    63,    95,   265,   268,    71,    72,    18,    19,
      79,    21,    22,   151,   223,   224,    74,   152,   321,   322,
      73,   179,   208,   209,   180,    75,    76,   328,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    95,    27,   196,
     258,    77,    78,   259,   298,    30,   153,   283,    83,   187,
     284,   221,   331,   129,   134,   332,   234,    84,    32,   239,
      85,   232,   233,    33,    86,    34,   105,   106,   107,   108,
     109,     1,    95,    87,   212,   247,   285,   212,    88,   340,
      89,   255,   256,     2,     3,     4,     5,     6,     7,     8,
      96,   262,   113,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,     2,     3,     4,     5,
       6,     7,     8,    90,   260,    93,   119,   131,   133,   110,
     134,   138,   -48,    95,   143,   146,   147,    17,   148,    18,
      19,    20,    21,    22,   302,   149,   150,   154,   181,   177,
     182,   299,   189,     2,     3,     4,     5,     6,     7,     8,
     305,    23,    24,   183,   309,   191,   197,    25,    26,    27,
      28,    29,   192,   194,   201,   198,    30,   200,   212,    31,
     206,   203,   301,   211,   207,   217,   210,   218,   220,    32,
     222,   238,   227,   240,    33,   228,    34,   261,    35,   257,
      36,    37,    38,    39,    40,    41,   263,   272,    91,   231,
      12,   273,   275,    17,   278,    18,    19,    20,    21,    22,
     348,   274,   236,   237,   251,   252,   281,   287,   290,     2,
       3,     4,     5,     6,     7,     8,   286,    23,    24,   292,
     294,   295,   345,    25,    26,    27,    28,    29,   297,   300,
     296,   303,    30,   313,   306,    31,   311,   308,   330,   334,
     307,   310,   312,   316,   335,    32,    95,   336,   338,   337,
      33,   339,    34,   341,    35,   342,    36,    37,    38,    39,
      40,    41,   343,   235,    96,   347,    12,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      95,   350,   349,   353,   354,   264,   351,   355,   356,   185,
     291,   346,    95,   190,   304,     0,     0,     0,    96,     0,
       0,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    95,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   216,   254,     0,     0,
       0,     0,    96,     0,     0,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   270,     0,     0,     0,     0,    96,     0,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   288,     0,     0,     0,   142,
      96,    95,     0,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   178,     0,    95,    96,
       0,     0,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   193,    96,    95,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,     0,     0,   195,    96,    95,     0,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,     0,     0,   199,    96,    95,     0,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     219,     0,     0,    96,    95,     0,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   253,
       0,     0,    96,    95,     0,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   271,     0,
       0,    96,    95,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   282,     0,     0,
      96,    95,     0,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   289,     0,     0,    96,
      95,     0,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   293,     0,    95,    96,     0,
       0,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   317,    96,    95,     0,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   325,     0,     0,    96,    95,     0,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     329,     0,     0,    96,    95,     0,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   352,
      95,     0,    96,     0,     0,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    96,    95,
       0,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,     0,     0,     0,     0,     0,     0,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-289))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    30,    42,    32,    33,   130,   187,    38,   296,     3,
       3,    38,    44,    40,    44,     7,     5,     5,     7,     0,
      74,     5,   203,     5,   205,    17,    18,    19,    20,    21,
      22,    23,     5,    24,    38,    29,    29,    66,    67,    71,
      44,    71,    73,    72,   332,     5,    75,     7,    77,    38,
       0,    40,    40,     5,    41,    84,    40,    44,    40,    38,
       5,     5,    41,    44,    55,    56,    57,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,    62,    75,    75,    73,   114,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    40,    40,    70,    40,    10,
      11,    12,    71,    24,   229,   230,    40,    40,     3,     4,
       5,     6,     7,    38,    27,    28,    40,    42,    29,    30,
       5,    41,   151,   152,    44,    40,    40,   308,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    24,    33,   140,
      41,    40,     5,    44,   269,    40,    71,    38,    40,   130,
      41,   180,    41,    75,     5,    44,     7,    40,    53,   199,
       5,   190,   191,    58,     5,    60,    53,    54,    55,    56,
      57,     5,    24,    40,     3,   204,     5,     3,    40,     5,
      40,   210,   211,    17,    18,    19,    20,    21,    22,    23,
      42,   220,   173,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    17,    18,    19,    20,
      21,    22,    23,    40,   215,     5,    37,     5,    71,    71,
       5,     5,    36,    24,     5,    42,     5,     1,     5,     3,
       4,     5,     6,     7,   274,     5,     5,     5,    71,    64,
      40,   270,    41,    17,    18,    19,    20,    21,    22,    23,
     279,    25,    26,    75,   283,    38,    36,    31,    32,    33,
      34,    35,    44,    41,     7,    41,    40,    42,     3,    43,
      41,    44,   273,    38,    41,    38,    42,     5,    38,    53,
       3,    42,    71,     7,    58,    71,    60,     3,    62,    53,
      64,    65,    66,    67,    68,    69,    41,    41,    72,    71,
      74,     3,     3,     1,     7,     3,     4,     5,     6,     7,
     339,    63,    71,    71,    71,    71,    41,    71,     3,    17,
      18,    19,    20,    21,    22,    23,    41,    25,    26,    39,
      71,    53,   333,    31,    32,    33,    34,    35,    71,    71,
      40,    75,    40,     3,    71,    43,    41,    44,    41,     7,
      71,    71,    71,    71,     7,    53,    24,     7,    41,    76,
      58,    38,    60,    41,    62,    41,    64,    65,    66,    67,
      68,    69,    71,   192,    42,    71,    74,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      24,    71,    41,    41,    41,   225,    71,    71,    71,   129,
     259,   337,    24,    71,   276,    -1,    -1,    -1,    42,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    24,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,   173,    71,    -1,    -1,
      -1,    -1,    42,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    -1,    42,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    41,
      42,    24,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    39,    -1,    24,    42,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    41,    42,    24,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    -1,    41,    42,    24,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    -1,    41,    42,    24,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      39,    -1,    -1,    42,    24,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    39,
      -1,    -1,    42,    24,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    39,    -1,
      -1,    42,    24,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    39,    -1,    -1,
      42,    24,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    39,    -1,    -1,    42,
      24,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    39,    -1,    24,    42,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    41,    42,    24,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    39,    -1,    -1,    42,    24,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      39,    -1,    -1,    42,    24,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    39,
      24,    -1,    42,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    42,    24,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    17,    18,    19,    20,    21,    22,    23,    78,
      79,    84,    74,    90,    95,     0,     5,     1,     3,     4,
       5,     6,     7,    25,    26,    31,    32,    33,    34,    35,
      40,    43,    53,    58,    60,    62,    64,    65,    66,    67,
      68,    69,    83,    84,    85,    86,    87,    88,    90,    91,
      92,    96,    97,    98,   101,   102,   103,   104,   110,   118,
     120,   126,    40,    71,     5,     7,    38,    40,    73,   105,
     106,    40,    40,     5,    40,    40,    40,    40,     5,     5,
     110,   110,   110,    40,    40,     5,     5,    40,    40,    40,
      40,    72,    87,     5,    84,    24,    42,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      71,    81,    82,    84,    38,    73,   110,   110,   111,    37,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    75,
     112,     5,   110,    71,     5,    99,   100,   110,     5,   110,
      93,    94,    41,     5,   110,   119,    42,     5,     5,     5,
       5,    38,    42,    71,     5,     5,    40,   115,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,    41,    44,     5,    70,   110,    64,    39,    41,
      44,    71,    40,    75,   107,   106,     7,    84,   107,    41,
      71,    38,    44,    41,    41,    41,    90,    36,    41,    41,
      42,     7,   121,    44,    38,    44,    41,    41,   110,   110,
      42,    38,     3,   116,   117,    80,    82,    38,     5,    39,
      38,   110,     3,    27,    28,   108,   109,    71,    71,     5,
     115,    71,   110,   110,     7,   100,    71,    71,    42,    87,
       7,   122,   125,    44,    71,     5,   115,   110,     5,    40,
     115,    71,    71,    39,    71,   110,   110,    53,    41,    44,
      90,     3,   110,    41,   109,   107,     3,    29,   107,   113,
      71,    39,    41,     3,    63,     3,    44,    71,     7,    38,
      41,    41,    39,    38,    41,     5,    41,    71,    71,    39,
       3,   117,    39,    39,    71,    53,    40,    71,   107,   110,
      71,    90,    87,    75,   125,   110,    71,    71,    44,   110,
      71,    41,    71,     3,   113,   114,    71,    41,    10,    11,
      12,    29,    30,   123,   124,    39,     5,    40,   115,    39,
      41,    41,    44,    89,     7,     7,     7,    76,    41,    38,
       5,    41,    41,    71,   113,    90,   124,    71,   110,    41,
      71,    71,    39,    41,    41,    71,    71
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
		(yyval.stmt)=new /*Statement::*/ FunctionStatement(FUNC_DEFN, qscript_parser::line_no,
			nest_lev, flagIsAForBody_, scope_, v_list, funcBody_, search_for, returnType_);
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
#line 227 "src/q.ypp"
    {
		 (yyval.v_list)=(yyvsp[(1) - (1)].v_list);
		 //cout << "got decl_comma_list : " << endl;
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 231 "src/q.ypp"
    {
		(yyval.v_list)=qscript_parser::link_chain((yyvsp[(1) - (3)].v_list),(yyvsp[(3) - (3)].v_list));
		//cout << "chaining var_decl : " << endl;
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 237 "src/q.ypp"
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
#line 244 "src/q.ypp"
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
#line 253 "src/q.ypp"
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
#line 262 "src/q.ypp"
    {
		(yyval.v_list)=0;
		}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 270 "src/q.ypp"
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
#line 279 "src/q.ypp"
    {
		(yyvsp[(1) - (2)].stmt) -> next_ = (yyvsp[(2) - (2)].stmt);
		(yyvsp[(2) - (2)].stmt) -> prev_ = (yyvsp[(1) - (2)].stmt);
		(yyval.stmt) = (yyvsp[(2) - (2)].stmt);
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 296 "src/q.ypp"
    {
		   (yyval.type_qual) = CONST_QUAL;
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 301 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (3)].name), (yyvsp[(1) - (3)].dt)/*, line_no*/);
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 304 "src/q.ypp"
    {
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 306 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (5)].name), (yyvsp[(1) - (5)].dt), (yyvsp[(4) - (5)].expr));
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 309 "src/q.ypp"
    {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		DataType dt=DataType(INT8_ARR_TYPE+((yyvsp[(1) - (6)].dt)-INT8_TYPE));
		(yyval.stmt) = qscript_parser::active_scope->insert((yyvsp[(2) - (6)].name), dt, (yyvsp[(4) - (6)].expr)/*, line_no*/);
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 324 "src/q.ypp"
    {
		(yyval.stmt) = (yyvsp[(1) - (1)].c_stmt);
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 336 "src/q.ypp"
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

  case 42:

/* Line 1806 of yacc.c  */
#line 356 "src/q.ypp"
    {
		++qscript_parser::flagIsAForBody_;
		qscript_parser::for_loop_max_counter_stack.push_back ((yyvsp[(5) - (8)].expr));
	}
    break;

  case 43:

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

  case 44:

/* Line 1806 of yacc.c  */
#line 375 "src/q.ypp"
    {
		using qscript_parser::line_no;
	 	//cout << "line_no: " << line_no << endl;
		(yyval.c_stmt) = qscript_parser::ProcessCompoundStatement((yyvsp[(1) - (3)].c_stmt), (yyvsp[(2) - (3)].stmt));

	  	//cout << "cmpd_stmt '}':  << blk_question_start_flag.size(): "
		//	<< qscript_parser::blk_question_start_flag.size()
		//	<< ", line_no: " << qscript_parser::line_no
		//	<< endl;
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 390 "src/q.ypp"
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

  case 46:

/* Line 1806 of yacc.c  */
#line 418 "src/q.ypp"
    {qscript_parser::globalActivePageName_ = (yyvsp[(2) - (2)].name); cout << "globalActivePageName_: " << qscript_parser::globalActivePageName_ << endl; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 418 "src/q.ypp"
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
		//cout << "parsed a PAGE_STMT : qscript_parser::page_nest_lev"
		//	<< qscript_parser::page_nest_lev << endl
		//	<< "page_name: " << qscript_parser::globalActivePageName_
		//	<< endl;
		qscript_parser::globalActivePageName_ = string("");
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 436 "src/q.ypp"
    {qscript_parser::globalActivePageName_ = (yyvsp[(2) - (2)].name);}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 436 "src/q.ypp"
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
		//cout << "parsed a PAGE_STMT : qscript_parser::page_nest_lev"
		//	<< qscript_parser::page_nest_lev << endl
		//	<< "grid_size: " << grid_size << endl
		//	<< "page_name: " << qscript_parser::globalActivePageName_ << endl
		//	<< endl;
		qscript_parser::globalActivePageName_ = string("");
	}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 455 "src/q.ypp"
    {
	  	//cout << "open_curly:  << blk_question_start_flag.size(): "
		//	<< qscript_parser::blk_question_start_flag.size()
		//	<< ", line_no: " << qscript_parser::line_no
		//	<< endl;
		CompoundStatement * cmpdStmt = qscript_parser::ProcessOpenCurly();
		//qscript_parser::compound_body_stack.push_back(cmpdStmt);
		//cmpdStmt->nestedCompoundStatementStack_=qscript_parser::compound_body_stack;
		(yyval.c_stmt)=cmpdStmt;
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 469 "src/q.ypp"
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

  case 52:

/* Line 1806 of yacc.c  */
#line 488 "src/q.ypp"
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

  case 53:

/* Line 1806 of yacc.c  */
#line 529 "src/q.ypp"
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

  case 54:

/* Line 1806 of yacc.c  */
#line 549 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new GotoStatement(GOTO_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(2) - (3)].name));
		// free($2); ? is this required here
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 556 "src/q.ypp"
    {
			clear_questions_list.push_back ((yyvsp[(1) - (1)].ue2expr));
		}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 559 "src/q.ypp"
    {
		  	clear_questions_list.push_back ((yyvsp[(3) - (3)].ue2expr));
		}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 564 "src/q.ypp"
    {
		string question_name((yyvsp[(1) - (1)].name));
		int exists = qscript_parser::question_exists (question_name);
		if (exists == -1) {
			std::stringstream err_text;
			err_text << "Question  " << question_name <<
				" does not exist ";
			print_err(compiler_sem_err, err_text.str(),
				qscript_parser::line_no, __LINE__, __FILE__);
		}
		(yyval.ue2expr) = new Unary2Expression ((yyvsp[(1) - (1)].name), oper_name);
	     }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 576 "src/q.ypp"
    {
		string question_name((yyvsp[(1) - (4)].name));
		int exists = qscript_parser::question_exists (question_name);
		if (exists == -1) {
			std::stringstream err_text;
			err_text << "Question  " << question_name <<
				" does not exist ";
			print_err(compiler_sem_err, err_text.str(),
				qscript_parser::line_no, __LINE__, __FILE__);
		}
		(yyval.ue2expr) = new Unary2Expression (oper_arrderef, (yyvsp[(1) - (4)].name), (yyvsp[(3) - (4)].expr));
		}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 604 "src/q.ypp"
    {
	  	//$$ = 0;
		(yyval.stmt) = new ClearStatement (CLEAR_STMT, qscript_parser::line_no,
			qscript_parser::nest_lev, qscript_parser::flagIsAForBody_,
			clear_questions_list, (yyvsp[(5) - (7)].text_buf));
		clear_questions_list.clear();
	  }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 613 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new ColumnStatement(COLUMN_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr));
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 620 "src/q.ypp"
    {
		using qscript_parser::nest_lev;
		using qscript_parser::flagIsAForBody_;
		(yyval.stmt) = new NewCardStatement(COLUMN_STMT, qscript_parser::line_no, nest_lev, flagIsAForBody_, (yyvsp[(3) - (5)].expr));
	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 628 "src/q.ypp"
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

  case 63:

/* Line 1806 of yacc.c  */
#line 642 "src/q.ypp"
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

  case 64:

/* Line 1806 of yacc.c  */
#line 655 "src/q.ypp"
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

  case 65:

/* Line 1806 of yacc.c  */
#line 665 "src/q.ypp"
    {
		string path_to_media ((yyvsp[(4) - (5)].text_buf));
		(yyval.stmt) = qscript_parser::ProcessVideoQuestion((yyvsp[(1) - (5)].name), "dummy question text", path_to_media);
		text_expr_vec.clear();
		question_attributes.Reset();
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 671 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::ProcessCaptureQuestion((yyvsp[(1) - (5)].name), "dummy question text");
		text_expr_vec.clear();
		question_attributes.Reset();
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 676 "src/q.ypp"
    {
		qscript_parser::q_type = geocode_gmapv3;
		(yyval.stmt) = qscript_parser::ProcessGeocodeQuestion((yyvsp[(1) - (5)].name), qscript_parser::q_type);
		qscript_parser::has_a_geocode_question  = true;
		question_attributes.Reset();
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 690 "src/q.ypp"
    {
		text_expr_vec.push_back (new TextExpression(string((yyvsp[(1) - (1)].text_buf))));
	}
    break;

  case 71:

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

  case 72:

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
				text_expr_vec.push_back (new TextExpression(se->question_, (yyvsp[(5) - (6)].expr)) );
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
#line 735 "src/q.ypp"
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
#line 768 "src/q.ypp"
    {
		question_attributes.setHidden();
	}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 771 "src/q.ypp"
    {
		question_attributes.setAllowBlank();
	}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 777 "src/q.ypp"
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
#line 786 "src/q.ypp"
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
#line 795 "src/q.ypp"
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
#line 804 "src/q.ypp"
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
#line 813 "src/q.ypp"
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
#line 822 "src/q.ypp"
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
#line 831 "src/q.ypp"
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
#line 840 "src/q.ypp"
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
#line 849 "src/q.ypp"
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
#line 858 "src/q.ypp"
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
#line 867 "src/q.ypp"
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
#line 876 "src/q.ypp"
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
#line 885 "src/q.ypp"
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
#line 894 "src/q.ypp"
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
#line 903 "src/q.ypp"
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
#line 912 "src/q.ypp"
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
#line 921 "src/q.ypp"
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
#line 930 "src/q.ypp"
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
#line 938 "src/q.ypp"
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
#line 946 "src/q.ypp"
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
#line 954 "src/q.ypp"
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
#line 1008 "src/q.ypp"
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
#line 1015 "src/q.ypp"
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
#line 1022 "src/q.ypp"
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
#line 1031 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression((yyvsp[(3) - (4)].name), oper_to_string);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1037 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].name), 0, oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1043 "src/q.ypp"
    {
		(yyval.expr) = new Binary2Expression((yyvsp[(1) - (6)].expr), (yyvsp[(3) - (6)].name), (yyvsp[(5) - (6)].expr), oper_in);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1049 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_isanswered);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1055 "src/q.ypp"
    {
		(yyval.expr) = new Unary2Expression ((yyvsp[(3) - (4)].name), oper_count);
		if(qscript_parser::XTCC_DEBUG_MEM_USAGE){
			mem_log((yyval.expr), __LINE__, __FILE__, qscript_parser::line_no);
		}
	}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1073 "src/q.ypp"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1074 "src/q.ypp"
    {
		(yyval.expr)=qscript_parser::link_chain((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));
	}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1079 "src/q.ypp"
    {
	       qscript_parser::q_type = spn;
	       // we need this =1 when generating
	       // code for flat file creation
		qscript_parser::no_mpn = 1;
	}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1085 "src/q.ypp"
    { qscript_parser::q_type = mpn;
		qscript_parser::no_mpn = (yyvsp[(3) - (4)].ival);
	}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1088 "src/q.ypp"
    {
	       qscript_parser::q_type = video;
	}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1091 "src/q.ypp"
    {
	       qscript_parser::q_type = image;
	}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1094 "src/q.ypp"
    {
	       qscript_parser::q_type = audio;
	}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1097 "src/q.ypp"
    {
	       qscript_parser::q_type = video_capture;
	}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1100 "src/q.ypp"
    {
	       qscript_parser::q_type = image_capture;
	}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1103 "src/q.ypp"
    {
	       qscript_parser::q_type = audio_capture;
	}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1108 "src/q.ypp"
    {
		     qscript_parser::has_mutex_range = true;
	     }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1118 "src/q.ypp"
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

  case 123:

/* Line 1806 of yacc.c  */
#line 1129 "src/q.ypp"
    {
		qscript_parser::mutex_range_set.add_indiv((yyvsp[(1) - (1)].ival));
	}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1135 "src/q.ypp"
    { }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1143 "src/q.ypp"
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

  case 128:

/* Line 1806 of yacc.c  */
#line 1155 "src/q.ypp"
    {
		//qscript_parser::xs.indiv.insert($1);
		qscript_parser::xs.add_indiv((yyvsp[(1) - (1)].ival));
	}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1161 "src/q.ypp"
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

  case 130:

/* Line 1806 of yacc.c  */
#line 1182 "src/q.ypp"
    {
		using qscript_parser::line_no;
		using qscript_parser:: stub_list;
		using qscript_parser:: named_stubs_list;
		//cout <<"got attribute_list size: " << attribute_list.size() << endl;
		string stub_name=(yyvsp[(2) - (6)].name);
		struct named_range* nr_ptr= new named_range(NAMED_RANGE
				, line_no, stub_name,stub_list);
		named_stubs_list.push_back(nr_ptr);
		//bool success = qscript_parser::verify_stubs_list (nr_ptr);
		//$$=0;
		(yyval.stmt) = nr_ptr;
	}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1197 "src/q.ypp"
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

  case 132:

/* Line 1806 of yacc.c  */
#line 1211 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(1) - (1)].text_buf));
	}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1214 "src/q.ypp"
    {
		vec_named_attribute_list.push_back ((yyvsp[(3) - (3)].text_buf));
	}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1226 "src/q.ypp"
    {
		 }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1231 "src/q.ypp"
    {
		current_stub_pair_options.is_mutex = true;
	   }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1234 "src/q.ypp"
    {
		current_stub_pair_options.is_other_specify = true;
	   }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1237 "src/q.ypp"
    {
	   	current_stub_pair_options.stub_media_type = stub_pair_options::image;
	   	current_stub_pair_options.url = (yyvsp[(2) - (2)].text_buf);
	   }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1241 "src/q.ypp"
    {
	   	current_stub_pair_options.stub_media_type = stub_pair_options::audio;
	   	current_stub_pair_options.url = (yyvsp[(2) - (2)].text_buf);
		}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1246 "src/q.ypp"
    {
	   	current_stub_pair_options.stub_media_type = stub_pair_options::video;
	   	current_stub_pair_options.url = (yyvsp[(2) - (2)].text_buf);
		}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1252 "src/q.ypp"
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

  case 144:

/* Line 1806 of yacc.c  */
#line 1285 "src/q.ypp"
    {
		string s1 = (yyvsp[(1) - (4)].text_buf);
		int32_t code = (yyvsp[(2) - (4)].ival);
		cout << "parsed stub with options" << endl;
		qscript_parser::do_stub_pair_checks (s1, code, current_stub_pair_options);
		current_stub_pair_options.reset();
	}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1361 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), 0, (yyvsp[(5) - (7)].name), 0);
	}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1365 "src/q.ypp"
    {
		AbstractExpression * a_expr = (yyvsp[(7) - (10)].expr);
		Unary2Expression * arr_r_index
			= dynamic_cast<Unary2Expression*> (a_expr);
		//$$ = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
		//		, $3, $5, $7);
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

  case 147:

/* Line 1806 of yacc.c  */
#line 1384 "src/q.ypp"
    {
                // 2nd NAME is an expression
                Unary2Expression * un2e = new Unary2Expression ((yyvsp[(6) - (9)].name), oper_name);
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (9)].name), 0, un2e);
	}
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1390 "src/q.ypp"
    {
		cout << __LINE__ << "|^: reached here" << endl;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (13)].name), (yyvsp[(5) - (13)].expr), (yyvsp[(8) - (13)].name), (yyvsp[(10) - (13)].expr));
        }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1395 "src/q.ypp"
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

  case 150:

/* Line 1806 of yacc.c  */
#line 1409 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), 0, (yyvsp[(5) - (7)].name), 0);
	}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1413 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), 0, (yyvsp[(5) - (10)].name), (yyvsp[(7) - (10)].expr));
	}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1417 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (10)].name), (yyvsp[(5) - (10)].expr), xs);
		xs.reset();
        }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1423 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_ADD
				, (yyvsp[(3) - (7)].name), 0, xs);
		xs.reset();
	}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1429 "src/q.ypp"
    {
		using qscript_parser::xs;
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt( STUB_MANIP_DEL
				, (yyvsp[(3) - (7)].name), 0, xs);
		xs.reset();
	}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1435 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_UNSET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1438 "src/q.ypp"
    {
		(yyval.stmt) = qscript_parser::setup_stub_manip_stmt_set_unset( STUB_MANIP_SET_ALL, (yyvsp[(3) - (5)].name));
	}
    break;



/* Line 1806 of yacc.c  */
#line 3634 "src/q.cpp"
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
#line 1446 "src/q.ypp"



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
	if (tmp==-1) {
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
		//cout << __PRETTY_FUNCTION__ << ", blk_question_start_flag.size(): "
		//	<< blk_question_start_flag.size()
		//	<< endl;
		blk_question_start_flag.pop_back();
		//cout << __PRETTY_FUNCTION__ << ", after pop_back blk_question_start_flag.size(): "
		//	<< blk_question_start_flag.size()
		//	<< endl;
		if (blk_question_start_flag.size() > 0) {
			flag_next_question_start_of_block = blk_question_start_flag.back();
		}
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
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	vector <ActiveVariableInfo* > av_info;
	PrintActiveVariablesAtScope(active_scope_list, av_info);
	CompoundStatement * cmpd_stmt_ptr=stack_cmpd_stmt.back();

	GeocodeGMapV3Question * geo_code_question = 0;
	if (qscript_parser::flagIsAForBody_) {
		cerr << " GEOCODE_GMAPV3 within for loops not yet implemented - exiting"
			<< endl;
		exit (1);
	} else {
		geo_code_question = new GeocodeGMapV3Question (QUESTION_TYPE, line_no
						, nest_lev, flagIsAForBody_
						, name, ::text_expr_vec, q_type
						, cmpd_stmt_ptr
						, av_info, question_attributes);
		question_list.push_back(geo_code_question);
	}
	++(cmpd_stmt_ptr->counterContainsQuestions_);
	if (flag_next_question_start_of_block) {
		geo_code_question->isStartOfBlock_ = true;
		flag_next_question_start_of_block = false;
	}
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
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

