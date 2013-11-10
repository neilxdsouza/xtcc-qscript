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
     VIDEO_CAPTURE = 268,
     AUDIO_CAPTURE = 269,
     IMAGE_CAPTURE = 270,
     VOID_T = 271,
     INT8_T = 272,
     INT16_T = 273,
     INT32_T = 274,
     FLOAT_T = 275,
     DOUBLE_T = 276,
     STRING_T = 277,
     IN = 278,
     FOR = 279,
     GOTO = 280,
     HIDDEN = 281,
     ALLOW_BLANK = 282,
     MUTEX = 283,
     OTHER = 284,
     CLEAR = 285,
     COLUMN = 286,
     ISANSWERED = 287,
     NEWCARD = 288,
     PAGE = 289,
     GRID_SIZE = 290,
     RANDOMIZE = 291,
     CONST = 292,
     LOGOR = 293,
     LOGAND = 294,
     NOEQ = 295,
     ISEQ = 296,
     GEQ = 297,
     LEQ = 298,
     NOT = 299,
     UMINUS = 300,
     COUNT = 301,
     FUNC_CALL = 302,
     IF = 303,
     ELSE = 304,
     STUBS_LIST = 305,
     NAMED_ATTRIBUTES = 306,
     SETDEL = 307,
     SETADD = 308,
     UNSET = 309,
     SETALL = 310
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
#line 122 "src/q.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


