/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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
     PAGE = 291,
     GRID_SIZE = 292,
     RANDOMIZE = 293,
     CONST = 294,
     LOGOR = 295,
     LOGAND = 296,
     NOEQ = 297,
     ISEQ = 298,
     GEQ = 299,
     LEQ = 300,
     NOT = 301,
     UMINUS = 302,
     COUNT = 303,
     FUNC_CALL = 304,
     IF = 305,
     ELSE = 306,
     STUBS_LIST = 307,
     NAMED_ATTRIBUTES = 308,
     SETDEL = 309,
     SETADD = 310,
     UNSET = 311,
     SETALL = 312
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
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



/* Line 2068 of yacc.c  */
#line 124 "src/q.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


