%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "def.h"
int line = 1;
Value lexval;

char* newstring(char* s) {
    char* p = malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}
%}

%option noyywrap

delimiter   [ \t\r]
comment     \/\/.*
spacing     {delimiter}+
letter      [A-Za-z_]
digit       [0-9]
intconst    {digit}+
strconst    \"([^\"\n])*\"
boolconst   false|true
realconst   {digit}+\.[0-9]+
id          {letter}({letter}|{digit})*

%%

{spacing}   ;
{comment}   ;
"\n"          {line++;}
"integer"     {return(INTEGER);}
"string"      {return(STRING);}
"boolean"     {return(BOOLEAN);}
"real"        {return(REAL);}
"type"        {return(TYPE);}
"var"         {return(VAR);}
"func"        {return(FUNC_P);}
"body"        {return(BODY);}
"if"          {return(IF);}
"then"        {return(THEN);}
"elsif"       {return(ELSIF);}
"else"        {return(ELSE);}
"while"       {return(WHILE);}
"for"         {return(FOR);}
"to"          {return(TO);}
"do"          {return(DO);}
"end"         {return(END);}
"and"         {return(AND);}
"or"          {return(OR);}
"not"         {return(NOT);}
"in"          {return(IN);}
"read"        {return(READ_P);}
"head"        {return(HEAD_P);}
"tail"        {return(TAIL_P);}
"empty"       {return(EMPTY);}
"write"       {return(WRITE);}
"writeln"     {return(WRITELN);}
"="           {return(ASSIGN);}
"=="          {return(EQUAL);}
"!="          {return(NOT_EQUAL);}
"<="          {return(LESS_EQUAL);}
">="          {return(GREATER_EQUAL);}
"<"           {return(LESS);}
">"           {return(GREATER);}
"+"           {return(PLUS);}
"-"           {return(MINUS);}
"*"           {return(TIMES);}
"/"           {return(DIVIDE);}
"++"          {return(CONCAT);}
"|"           {return(MOD);}
".."          {return(RANGE);}
","           {return(COMMA);}
":"           {return(COLON);}
";"           {return(SEMICOLON);}
"."           {return(DOT);}
"{"           {return(LBRACE);}
"}"           {return(RBRACE);}
"["           {return(LBRACKET);}
"]"           {return(RBRACKET);}
"("           {return(LPARENTESIS);}
")"           {return(RPARENTESIS);}

{intconst}    {lexval.ival = atoi(yytext); return(INTCONST);}
{strconst}    {lexval.sval = newstring(yytext); return(STRCONST);}
{boolconst}   {lexval.ival = (yytext[0] == 'f' ? 0 : 1); return(BOOLCONST);}
{realconst}   {lexval.rval = atof(yytext); return(REALCONST);}
{id}          {lexval.sval = newstring(yytext); return(ID);}

.             {printf("Unknown character: %s\n", yytext);}

%%  