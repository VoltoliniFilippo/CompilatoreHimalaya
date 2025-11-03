#include <stdio.h>
#include "def.h"

char* symbols[] =
{
    "PROGRAM",
    "TYPE_SECTION",
    "TYPE_DECL",
    "TYPE",
    "STRUCT_TYPE",
    "ATOMIC_DECL",
    "VECTOR_TYPE",
    "VAR_SECTION",
    "VAR_DECL",
    "FUNC_SECTION",
    "FUNC_DECL",
    "FORMAL_DECL",
    "READ_STAT",
    "WRITE_STAT",
    "ASSIGN_STAT",
    "INDEXING",
    "IF_STAT",
    "OPT_ELSIF_STAT_LIST",
    "WHILE_STAT",
    "FOR_STAT",
    "LOGIC_EXPR",
    "COMP_EXPR",
    "MATH_EXPR",
    "NEG_EXPR",
    "BUILT_IN_EXPR",
    "LHS",
    "CONSTRUCTOR",
    "RANGE",
    "COND_EXPR",
    "FUNC_CALL",
    "ID",
    "INTCONST",
    "REALCONST",
    "STRCONST",
    "BOOLCONST",
    "INTEGER",
    "REAL",
    "STRING",
    "BOOLEAN"
};

char* semantic_values[] = {
  "BOOLEAN",
  "INTEGER",
  "REAL",
  "STRING",
  "ID",
  "AND",
  "OR",
  "NOVAL",
  "EQ",
  "NE",
  "GT",
  "GE",
  "LT",
  "LE",
  "IN",
  "PLUS",
  "MINUS",
  "PLUSPLUS",
  "TIMES",
  "DIVIDE",
  "BUILT_IN_INTEGER",
  "BUILT_IN_REAL",
  "BUILT_IN_EMPTY",
  "BUILT_IN_HEAD",
  "BUILT_IN_TAIL",
  "BOOLCONST",
  "INTCONST",
  "REALCONST",
  "STRCONST",
  "WRITE",
  "WRITELN",
  "NONTERMINAL",
  "STRUCT",
  "VECT", 
  "EMPTY",
  "HEAD",
  "TAIL",
  "CARD"
};

void treeprint(Pnode root, int indent)
{
    int i;
    Pnode p;
    
    for(i=0; i<indent; i++)
        printf("    ");
   
    printf("%s", symbols[root->symbol]);

    switch(root->symbol){
        case N_FUNC_CALL:
        case N_FUNC_DECL:
        case T_ID:
        case T_STRCONST:
            printf(" (%s)", root->value.sval);
            break;

        case T_INTCONST:
            printf(" (%d)", root->value.ival);
            break;

        case T_REALCONST:
            printf(" (%f)", root->value.rval);
            break;

        case N_LOGIC_EXPR:
        case N_COMP_EXPR:
        case N_MATH_EXPR:
        case N_NEG_EXPR:
        case N_BUILT_IN_EXPR:
        case N_CONSTRUCTOR:
        case N_WRITE_STAT:
            printf(" (%s)", semantic_values[root->value.ival]);
            break;

        default:
            break;
    }
    
    
    printf("\n");
    
    for(p=root->c1; p != NULL; p = p->b)
        treeprint(p, indent+1);

    for(p=root->c2; p != NULL; p = p->b)
        treeprint(p, indent+1);

    for(p=root->c3; p != NULL; p = p->b)
        treeprint(p, indent+1); 
        
    for(p=root->c4; p != NULL; p = p->b)
        treeprint(p, indent+1);
}