%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#define YYSTYPE Pnode
extern char *yytext;
extern int line;
extern Value lexval;
extern FILE *yyin;
int yylex();
Pnode root = NULL;
%}

%token TYPE ID BOOLEAN INTEGER REAL STRING VAR FUNC_P END AND OR EQUAL NOT_EQUAL GREATER GREATER_EQUAL LESS LESS_EQUAL 
%token IN PLUS MINUS CONCAT TIMES DIVIDE NOT EMPTY HEAD_P TAIL_P BOOLCONST INTCONST REALCONST STRCONST IF THEN ELSE 
%token BODY READ_P ELSIF WHILE DO FOR TO WRITE WRITELN
%token COMMA COLON SEMICOLON ASSIGN MOD RANGE DOT
%token LBRACE RBRACE /*{}*/ LBRACKET RBRACKET /*[]*/ LPARENTESIS RPARENTESIS /*()*/
%%

program : type_section var_section func_section body_section
        {
            root = $$ = newnode(N_PROGRAM);
            $$->c1 = $1; //type section
            $$->c2 = $2; //var section
            $$->c3 = $3; //func section
            $$->c4 = $4; //body section
        }
        ;

type_section: TYPE type_decl_list {$$ = $2;}
            | {$$ = NULL;}
            ;

type_decl_list: type_decl type_decl_list {$$ = $1; $$->b = $2;}
              | type_decl {$$ = $1;}
              ;

type_decl: id_list ASSIGN type SEMICOLON {$$ = newnode(N_TYPE_DECL); $$->c1 = $1; $$->c2 = $3;}
         ; //ASSIGN = '='

id_list: ID {$$ = idnode();} COMMA id_list {$$ = $2; $2->b = $4;}
        | ID {$$ = idnode();}
        ;

type: atomic_type
    | struct_type
    | vector_type
    ;

atomic_type:  BOOLEAN {$$ = newnode(T_BOOLEAN);}
            | INTEGER {$$ = newnode(T_INTEGER);}
            | REAL {$$ = newnode(T_REAL);}
            | STRING {$$ = newnode(T_STRING);}
            | ID {$$ = idnode();}
            ;

struct_type: LBRACE atomic_decl_list RBRACE {$$ = newnode(N_STRUCT_TYPE); $$->c1 = $2;}
           ;

atomic_decl_list: atomic_decl COMMA atomic_decl_list {$$ = $1; $$->b = $3;}
                 | atomic_decl {$$ = $1;}
                 ;

atomic_decl: ID {$$ = idnode();} COLON atomic_type {$$ = newnode(N_ATOMIC_DECL); $$->c1 = $2; $$->c2 = $4;}
           ;

vector_type: LBRACKET vector_elem_type RBRACKET {$$ = newnode(N_VECTOR_TYPE);$$->c1 = $2;}
           ;//BRACKETS = '[]'

vector_elem_type: atomic_type
                | struct_type
                ; //tolto ID perché faceva già parte di atomic_type

var_section: VAR var_decl_list {$$ = $2;}
           | {$$ = NULL;}
           ;

var_decl_list: var_decl var_decl_list {$$ = $1; $$->b = $2;}
              | var_decl
              ;
            
var_decl: id_list COLON type SEMICOLON {$$ = newnode(N_VAR_DECL); $$->c1 = $1; $$->c2 = $3;}
        ;

func_section: FUNC_P func_decl_list {$$ = $2;}
            | {$$ = NULL;}
            ;

        
func_decl_list: func_decl func_decl_list {$$ = $1; $1->b = $2;}
              | func_decl {$$ = $1;}
              ;

func_decl: ID {$$ = newnode(N_FUNC_DECL); $$->value.sval = lexval.sval;} LPARENTESIS opt_formal_decl_list RPARENTESIS COLON type expr END {$$ = $2; $$->c1 = $4; $$->c2 = $7; $$->c3 = $8;}
         ; //LPARENTESIS = '(' e RPARENTESIS = ')'

opt_formal_decl_list: formal_decl_list {$$ = $1;}
                     | {$$ = NULL;}
                     ;

formal_decl_list: formal_decl COMMA formal_decl_list {$$ = $1; $1->b = $3;}
                | formal_decl
                ;

formal_decl: ID {$$ = idnode();} COLON type {$$ = $2; $2->c1 = $4;}
           ;

expr: expr bool_op bool_term {$$ = $2; $$->c1 = $1; $$->c2 = $3;}
    | bool_term
    ;

bool_op: AND {$$ = newnode(N_LOGIC_EXPR); $$->value.ival = VAL_AND;}
       | OR {$$ = newnode(N_LOGIC_EXPR); $$->value.ival = VAL_OR;}
       ;

bool_term: comp_term comp_op comp_term {$$ = $2; $$->c1 = $1; $$->c2 = $3;}
         | comp_term
         ;

comp_op: EQUAL {$$ = newnode(N_COMP_EXPR); $$->value.ival = VAL_EQ;}
       | NOT_EQUAL {$$ = newnode(N_COMP_EXPR); $$->value.ival = VAL_NE;}
       | GREATER {$$ = newnode(N_COMP_EXPR); $$->value.ival = VAL_GT;}
       | GREATER_EQUAL {$$ = newnode(N_COMP_EXPR); $$->value.ival = VAL_GE;}
       | LESS {$$ = newnode(N_COMP_EXPR); $$->value.ival = VAL_LT;}
       | LESS_EQUAL {$$ = newnode(N_COMP_EXPR); $$->value.ival = VAL_LE;}
       | IN {$$ = newnode(N_COMP_EXPR); $$->value.ival = VAL_IN;}
       ;

comp_term: comp_term add_op term {$$ = $2; $$->c1 = $1; $$->c2 = $3;}
         | term
         ;

add_op: PLUS {$$ = newnode(N_MATH_EXPR); $$->value.ival = VAL_PLUS;}
      | MINUS {$$ = newnode(N_MATH_EXPR); $$->value.ival = VAL_MINUS;}
      | CONCAT {$$ = newnode(N_MATH_EXPR); $$->value.ival = VAL_PLUSPLUS;}
      ;

term: term mul_op factor {$$ = $2; $$->c1 = $1; $$->c2 = $3;}
    | factor
    ;

mul_op: TIMES {$$ = newnode(N_MATH_EXPR); $$->value.ival = VAL_TIMES;}
      | DIVIDE {$$ = newnode(N_MATH_EXPR); $$->value.ival = VAL_DIVIDE;}
      ;

factor: unary_op factor {$$ = $1; $$->c1 = $2;}
      | LPARENTESIS expr RPARENTESIS {$$ = $2;}
      | MOD expr MOD {$$ = newnode(N_BUILT_IN_EXPR); $$->value.ival = VAL_CARD; $$->c1 = $2;}
      | lhs
      | built_in LPARENTESIS expr RPARENTESIS {$$ = $1; $$->c1 = $3;}
      | atomic_constant
      | struct_constructor
      | vector_constructor
      | range
      | cond_expr
      | func_call
      ;

unary_op: MINUS  {$$ = newnode(N_NEG_EXPR); $$->value.ival = VAL_MINUS;}
        | NOT {$$ = newnode(N_LOGIC_EXPR); $$->value.ival = VAL_NOT;}
        ;

built_in: INTEGER {$$ = newnode(N_BUILT_IN_EXPR); $$->value.ival = VAL_INTEGER;}
        | REAL {$$ = newnode(N_BUILT_IN_EXPR); $$->value.ival = VAL_REAL;}
        | EMPTY {$$ = newnode(N_BUILT_IN_EXPR); $$->value.ival = VAL_EMPTY;}
        | HEAD_P {$$ = newnode(N_BUILT_IN_EXPR); $$->value.ival = VAL_HEAD;}
        | TAIL_P {$$ = newnode(N_BUILT_IN_EXPR); $$->value.ival = VAL_TAIL;}
        ;

atomic_constant: BOOLCONST {$$ = boolconstnode();}
               | INTCONST {$$ = intconstnode();}
               | REALCONST {$$ = realconstnode();}
               | STRCONST {$$ = strconstnode();}
               ;

struct_constructor: LBRACE expr_list RBRACE {$$ = newnode(N_CONSTRUCTOR); $$->value.ival = VAL_STRUCT; $$->c1 = $2;}
                  ; 

expr_list: expr COMMA expr_list {$$ = $1; $$->b = $3;}
          | expr
          ;

cond_expr: IF expr THEN expr ELSE expr END {$$ = newnode(N_COND_EXPR); $$->c1 = $2; $$->c2 = $4; $$->c3 = $6;}
         ;

func_call: ID {$$ = newnode(N_FUNC_CALL); $$->value.sval = lexval.sval;} LPARENTESIS opt_expr_list RPARENTESIS {$$ = $2; $$->c1 = $4;}
          ;

opt_expr_list: expr_list
              | {$$ = NULL;}
              ;

vector_constructor: LBRACKET opt_expr_list RBRACKET {$$ = newnode(N_CONSTRUCTOR); $$->value.ival = VAL_VECT; $$->c1 = $2;}
                  ;

range: LBRACKET expr RANGE expr RBRACKET {$$ = newnode(N_RANGE); $$->c1 = $2; $$->c2 = $4;}
     ;

body_section: BODY stat_list END {$$ = $2;}
            ;

stat_list: stat SEMICOLON stat_list {$$ = $1; $1->b = $3;}
         | stat SEMICOLON {$$ = $1;}
         ;

stat: read_stat
    | write_stat
    | assign_stat
    | if_stat
    | while_stat
    | for_stat
    ;

read_stat: READ_P ID {$$ = newnode(N_READ_STAT); $$->c1 = idnode();}
          ;

write_stat: write_op expr {$$ = $1; $$->c1 = $2;}
          ;

write_op: WRITE {$$ = newnode(N_WRITE_STAT); $$->value.ival = VAL_WRITE;}
        | WRITELN {$$ = newnode(N_WRITE_STAT); $$->value.ival = VAL_WRITELN;}
        ;

assign_stat: lhs ASSIGN expr {$$ = newnode(N_ASSIGN_STAT); $$->c1 = $1; $$->c2 = $3;}
           ;

lhs: ID {$$ = idnode();} opt_fielding {$$ = newnode(N_LHS); $$->c1 = $2; $$->c2 = $3;}
    | indexing {$$ = newnode(N_LHS); $$->c1 = $1;}
    ;

opt_fielding: DOT ID {$$ = idnode();}
            | {$$ = NULL;}
            ;

indexing: ID {$$ = idnode();} LBRACKET expr RBRACKET opt_fielding {$$ = newnode(N_INDEXING); $$->c1 = $2; $$->c2 = $4; $$->c3 = $6;}
        ;

if_stat: IF expr THEN stat_list opt_elsif_stat_list opt_else_stat END {$$ = newnode(N_IF_STAT); $$->c1 = $2; $$->c2 = $4; $$->c3 = $5; $$->c4 = $6;}
       ;

opt_elsif_stat_list: ELSIF expr THEN stat_list opt_elsif_stat_list {$$ = newnode(N_OPT_ELSIF_STAT_LIST); $$->c1 = $2; $$->c2 = $4; $$->b = $5;}
                     | {$$ = NULL;}
                     ;

opt_else_stat: ELSE stat_list {$$ = $2;}
             | {$$ = NULL;}
             ;

while_stat: WHILE expr DO stat_list END {$$ = newnode(N_WHILE_STAT); $$->c1 = $2; $$->c2 = $4;}
          ; 

for_stat: FOR ID {$$ = idnode();} ASSIGN expr TO expr DO stat_list END {$$ = newnode(N_FOR_STAT); $$->c1 = $3; $$->c2 = $5; $$->c3 = $7; $$->c4 = $9;}
        ;

%%
Pnode idnode()
{
    Pnode p = newnode(T_ID);
    p->value.sval = lexval.sval;
    return(p);
}

Pnode keynode(Symbol keyword)
{
    return newnode(keyword);
}

Pnode intconstnode(){
    Pnode p = newnode(T_INTCONST);
    p->value.ival = lexval.ival;
    return(p);
}

Pnode realconstnode()
{
    Pnode p = newnode(T_REALCONST);
    p->value.rval = lexval.rval;
    return(p);
}

Pnode strconstnode()
{
    Pnode p = newnode(T_STRCONST);
    p->value.sval = lexval.sval;
    return(p);
}

Pnode boolconstnode()
{
    Pnode p = newnode(T_BOOLCONST);
    p->value.ival = lexval.ival;
    return(p);
}

Pnode newnode(Symbol symbol)
{
    Pnode p = malloc(sizeof(Node));
    p->symbol = symbol;
    p->line = line;
    p->c1 = p->c2 = p->c3 = p->c4 = NULL;
    p->b = NULL;
    return p;
}

void yyerror()
{
    fprintf(stderr, "Line %d: syntax error on symbol \"%s\"\n",line, yytext);
    exit(-1);
}

Code *genCode(){
    static Code gencode;
    int result;

    if((result = yyparse() == 0))
        gencode = semantic_analysis(root);

    /*
    print_symbol_table();
    treeprint(root, 0);
    print_generated_code(gencode);
    */

    return &gencode;
}

/*void main(){
    static Code gencode;
    int result;

    if((result = yyparse() == 0))
        gencode = semantic_analysis(root);
    
    print_generated_code(gencode);
}*/