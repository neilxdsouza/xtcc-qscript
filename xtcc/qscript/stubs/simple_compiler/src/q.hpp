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
     VOID_T = 268,
     INT8_T = 269,
     INT16_T = 270,
     INT32_T = 271,
     FLOAT_T = 272,
     DOUBLE_T = 273,
     STRING_T = 274,
     IN = 275,
     FOR = 276,
     GOTO = 277,
     HIDDEN = 278,
     ALLOW_BLANK = 279,
     MUTEX = 280,
     OTHER = 281,
     CLEAR = 282,
     COLUMN = 283,
     ISANSWERED = 284,
     NEWCARD = 285,
     FIX = 286,
     BRAND_RANK = 287,
     DRIVERS = 288,
     CREATE_1_0_EDIT = 289,
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

/* Line 2068 of yacc.c  */
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





/* Line 2068 of yacc.c  */
#line 125 "src/q.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


