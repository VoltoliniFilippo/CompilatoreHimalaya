#include "def.h"

typedef enum{
  HCOD,
  VARS,
  HALT,
  VALL,
  LOCI,
  LOCR,
  LOCS,
  LOAD,
  GROU,
  RNGE,
  LODA,
  INLD,
  CIDX,
  IXAD,
  STOR,
  SKIP,
  SKPF,
  EQUA,
  NEQU,
  GTHI,
  GEQI,
  LTHI,
  LEQI,
  GTHR,
  GEQR,
  LTHR,
  LEQR,
  GTHS,
  GEQS,
  LTHS,
  LEQS,
  BLNG,
  ADDI,
  SUBI, 
  MULI,
  DIVI,
  ADDR,
  SUBR,
  MULR,
  DIVR,
  NEGI,
  NEGR,
  NEGB,
  TORE,
  TOIN,
  EMPT,
  HEAD,
  TAIL,
  CARD,
  READ,
  WRTE,
  WRTL,
  PUSH,
  JUMP,
  APOP,
  FUNC,
  RETN
}Operator;

typedef struct stat_t{
  int address;
  Operator op;
  Value args[MAXARGS];
  struct stat_t *next;
}Stat;

typedef struct{
  Stat *head;
  int size;
  Stat *tail;
}Code;

//Macchina virtuale
typedef struct
{
  Operator op;
  Value args[MAXARGS];
} Hcode;

typedef struct{
  int size;
  int num;
  char *addr;
} Var;

typedef struct{
  int size;
  int num;
  char *addr;
  int var_index;
}Object;

typedef struct{
  int num;
  int objs;
  int ret;
} Activation;

int code_size(Code code);
void relocate(Code code, int offset);
Code appcode(Code code1, Code code2);
Code endcode();
Code concode(Code code1, Code code2, ...);
Stat *newstat(Operator op);
Code makecode(Operator op);
Code makecode1(Operator op, int arg);
Code makecode2(Operator op, int arg1, int arg2);
Code makecode3(Operator op, int arg1, int arg2,int arg3);
Code make_func_call(int numparams, int entry);
Code makecode_str(Operator op, char *arg);
Code make_vall(int size, int num);
Code make_loci(int value);
Code make_locr(float value);
Code make_locs(char *value);
Code make_load(int env, int oid);
Code make_loda(int env, int oid);
Code make_struct_grou(int fields, int size);
Code make_vect_grou(int fields, int size, int elements);
Code make_inld(int offset, int size);
Code make_fielding(int env, int oid, int offset, int size);
Code make_read(int oid, char *format);
Code make_ixad(int scale);
Code make_indexing(int scale, int offset, int size);
Code make_write(char *format);
Code make_writeln(char *format);
Code make_skip_exit(Operator op, int expr);
Code make_skip_offset(Operator op, int expr);
Code make_skip_up(Operator op, int expr);
Code make_func(int fid);
Code make_vars(int n);
Code make_hcod(int size);

char *remove_quotes(char *str);
char *get_format(Type *type);
char *construct_str(char *str, char c1, char c2);
char *get_format_struct(Type *type);
char *get_format_vect(Type *type);
char *get_domain_str(Domain domain);
char *get_type_str(Type *type);
int get_type_size(Type *type);
int get_type_size(Type *type);
int get_vect_size(Type *type);
int get_struct_size(Type *type);
int get_domain_size(Domain domain);
int get_expr_list_size(Pnode node);
int calc_offset(Field *fields, Field *field);
Code make_comp(Type *t1, Type *t2, SemanticValue op);
Code make_real_comp(SemanticValue op);
Code make_int_comp(SemanticValue op);
Code make_string_comp(SemanticValue op);
Code make_math(Type *t1, Type *t2, SemanticValue op);
Code make_int_math(SemanticValue op);
Code make_real_math(SemanticValue op);
Code make_neg(Type *t);
Code make_built_in(SemanticValue op);
int get_num_of_elements(SymbolTableEntry *entry);

void print_generated_code(Code code);
void print_args(Operator op, Value args[3]);

Code *genCode();