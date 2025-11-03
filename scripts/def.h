#define TOT 1000
#define MAX_SCOPE_DEPTH 100
#define SHIFT 4
#define MAXARGS 3
#define MAX_OBJECTS 1000
#define MAX_INSTANCES 1000
#define MAX_ACTIVATIONS 1000
#define SIZE_INT sizeof(int)
#define SIZE_FLOAT sizeof(float)

typedef union{
    int ival;
    float rval;
    char *sval;
}Value;

 typedef enum
 {
  N_PROGRAM,
  N_TYPE_SECTION,
  N_TYPE_DECL,
  N_TYPE,
  N_STRUCT_TYPE,
  N_ATOMIC_DECL,
  N_VECTOR_TYPE,
  N_VAR_SECTION,
  N_VAR_DECL,
  N_FUNC_SECTION,
  N_FUNC_DECL,
  N_FORMAL_DECL,
  N_READ_STAT,
  N_WRITE_STAT,
  N_ASSIGN_STAT,
  N_INDEXING,
  N_IF_STAT,
  N_OPT_ELSIF_STAT_LIST,
  N_WHILE_STAT,
  N_FOR_STAT,
  N_LOGIC_EXPR,
  N_COMP_EXPR,
  N_MATH_EXPR,
  N_NEG_EXPR,
  N_BUILT_IN_EXPR,
  N_LHS,
  N_CONSTRUCTOR,
  N_RANGE,
  N_COND_EXPR,
  N_FUNC_CALL,
  T_ID,
  T_INTCONST,
  T_REALCONST,
  T_STRCONST,
  T_BOOLCONST,
  T_INTEGER,
  T_REAL,
  T_STRING,
  T_BOOLEAN
}Symbol;

typedef enum{
  VAL_BOOLEAN,
  VAL_INTEGER,
  VAL_REAL,
  VAL_STRING,
  VAL_ID,
  VAL_AND,
  VAL_OR,
  VAL_NOT,
  VAL_EQ,
  VAL_NE,
  VAL_GT,
  VAL_GE,
  VAL_LT,
  VAL_LE,
  VAL_IN,
  VAL_PLUS,
  VAL_MINUS,
  VAL_PLUSPLUS,
  VAL_TIMES,
  VAL_DIVIDE,
  VAL_BUILT_IN_INTEGER,
  VAL_BUILT_IN_REAL,
  VAL_BUILT_IN_EMPTY,
  VAL_BUILT_IN_HEAD,
  VAL_BUILT_IN_TAIL,
  VAL_BOOLCONST,
  VAL_INTCONST,
  VAL_REALCONST,
  VAL_STRCONST,
  VAL_WRITE,
  VAL_WRITELN,
  VAL_NONTERMINAL,
  VAL_STRUCT,
  VAL_VECT,
  VAL_EMPTY,
  VAL_HEAD,
  VAL_TAIL,
  VAL_CARD
} SemanticValue;

extern int line;
extern Value lexval;

typedef struct snode
{
  Symbol symbol;
  Value value;
  int line;
  struct snode *c1, *c2, *c3, *c4, *b;
} Node;

typedef Node *Pnode;

// Funzioni nodi
Pnode newnode(Symbol symbol);
Pnode idnode();
Pnode keynode(Symbol keyword);
Pnode intconstnode();
Pnode realconstnode();
Pnode strconstnode();
Pnode boolconstnode();

void treeprint(Pnode, int),
     yyerror();

typedef enum{
  BOOLEAN_DOMAIN, INTEGER_DOMAIN, REAL_DOMAIN, STRING_DOMAIN, VECT_DOMAIN, STRUCT_DOMAIN, EMPTY_DOMAIN
}Domain;

typedef struct field_t{
  char *name;
  Domain domain;
  struct field_t *next;
}Field;

typedef struct type_t{
  Domain domain;
  Domain *child;
  Field *fields;
} Type;

typedef enum{
  TYPE_CLASS, VAR_CLASS, FUNC_CLASS, PARAM_CLASS
} Class;

typedef struct symbol_t{
  char *name;
  Class class;
  int oid;
  Type *type;
  struct symbol_t *formals;
  struct symbol_t *next;
}SymbolTableEntry;

// Funzioni symbol table
int hash(char* id);
SymbolTableEntry* lookup_symbol(char* name);
SymbolTableEntry* lookup_local(char* name);
SymbolTableEntry* insert_symbol(char* name, Class class, Type* type);
Type* create_type(Domain domain);
Type* create_vector_type(Domain *child, Field *fields);
Type* create_struct_type(Field* fields);
int count_vars();
void enter_scope();
void exit_scope();
void print_error(char* msg, char* name);
void print_symbol_table();