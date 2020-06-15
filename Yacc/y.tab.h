/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ENDFI = 0,
    WHILE = 1,
    IF = 2,
    THEN = 3,
    ELSE = 4,
    DO = 5,
    END = 6,
    IN = 7,
    OUT = 8,
    PLUS = 9,
    MINUS = 10,
    TIMES = 11,
    DIVIDE = 12,
    LP = 13,
    RP = 14,
    EQUAL = 15,
    ASSIGN = 16,
    LT = 17,
    GT = 18,
    SEMI = 19,
    INT10 = 20,
    INT8 = 21,
    INT16 = 22,
    FLO10 = 23,
    FLO8 = 24,
    FLO16 = 25,
    ID = 26,
    ERROR = 27
  };
#endif
/* Tokens.  */
#define ENDFI 0
#define WHILE 1
#define IF 2
#define THEN 3
#define ELSE 4
#define DO 5
#define END 6
#define IN 7
#define OUT 8
#define PLUS 9
#define MINUS 10
#define TIMES 11
#define DIVIDE 12
#define LP 13
#define RP 14
#define EQUAL 15
#define ASSIGN 16
#define LT 17
#define GT 18
#define SEMI 19
#define INT10 20
#define INT8 21
#define INT16 22
#define FLO10 23
#define FLO8 24
#define FLO16 25
#define ID 26
#define ERROR 27

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
