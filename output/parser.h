/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_OUTPUT_PARSER_H_INCLUDED
# define YY_YY_OUTPUT_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TYPE = 258,                    /* TYPE  */
    ID = 259,                      /* ID  */
    BOOLEAN = 260,                 /* BOOLEAN  */
    INTEGER = 261,                 /* INTEGER  */
    REAL = 262,                    /* REAL  */
    STRING = 263,                  /* STRING  */
    VAR = 264,                     /* VAR  */
    FUNC_P = 265,                  /* FUNC_P  */
    END = 266,                     /* END  */
    AND = 267,                     /* AND  */
    OR = 268,                      /* OR  */
    EQUAL = 269,                   /* EQUAL  */
    NOT_EQUAL = 270,               /* NOT_EQUAL  */
    GREATER = 271,                 /* GREATER  */
    GREATER_EQUAL = 272,           /* GREATER_EQUAL  */
    LESS = 273,                    /* LESS  */
    LESS_EQUAL = 274,              /* LESS_EQUAL  */
    IN = 275,                      /* IN  */
    PLUS = 276,                    /* PLUS  */
    MINUS = 277,                   /* MINUS  */
    CONCAT = 278,                  /* CONCAT  */
    TIMES = 279,                   /* TIMES  */
    DIVIDE = 280,                  /* DIVIDE  */
    NOT = 281,                     /* NOT  */
    EMPTY = 282,                   /* EMPTY  */
    HEAD_P = 283,                  /* HEAD_P  */
    TAIL_P = 284,                  /* TAIL_P  */
    BOOLCONST = 285,               /* BOOLCONST  */
    INTCONST = 286,                /* INTCONST  */
    REALCONST = 287,               /* REALCONST  */
    STRCONST = 288,                /* STRCONST  */
    IF = 289,                      /* IF  */
    THEN = 290,                    /* THEN  */
    ELSE = 291,                    /* ELSE  */
    BODY = 292,                    /* BODY  */
    READ_P = 293,                  /* READ_P  */
    ELSIF = 294,                   /* ELSIF  */
    WHILE = 295,                   /* WHILE  */
    DO = 296,                      /* DO  */
    FOR = 297,                     /* FOR  */
    TO = 298,                      /* TO  */
    WRITE = 299,                   /* WRITE  */
    WRITELN = 300,                 /* WRITELN  */
    COMMA = 301,                   /* COMMA  */
    COLON = 302,                   /* COLON  */
    SEMICOLON = 303,               /* SEMICOLON  */
    ASSIGN = 304,                  /* ASSIGN  */
    MOD = 305,                     /* MOD  */
    RANGE = 306,                   /* RANGE  */
    DOT = 307,                     /* DOT  */
    LBRACE = 308,                  /* LBRACE  */
    RBRACE = 309,                  /* RBRACE  */
    LBRACKET = 310,                /* LBRACKET  */
    RBRACKET = 311,                /* RBRACKET  */
    LPARENTESIS = 312,             /* LPARENTESIS  */
    RPARENTESIS = 313              /* RPARENTESIS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_OUTPUT_PARSER_H_INCLUDED  */
