
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     DRIVERS = 283,
     CONST = 284,
     LOGOR = 285,
     LOGAND = 286,
     NOEQ = 287,
     ISEQ = 288,
     GEQ = 289,
     LEQ = 290,
     NOT = 291,
     UMINUS = 292,
     COUNT = 293,
     FUNC_CALL = 294,
     IF = 295,
     ELSE = 296,
     STUBS_LIST = 297,
     SETDEL = 298,
     SETADD = 299,
     UNSET = 300,
     SETALL = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 55 "src/q.ypp"

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





/* Line 1676 of yacc.c  */
#line 116 "src/q.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


