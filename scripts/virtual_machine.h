#include "gen.h"

extern int pc, vp, ap, op, ip;

extern char istack[];
extern Var *vars;
extern Activation astack[];
extern Object ostack[];

extern int max_vars;
extern int input_exhausted;

void execute(Hcode *stat);
void load_hcode();

void error(const char *fmt, ...);
//Pop
int pop_int();
float pop_float();
Object pop_obj();

//Push
void push_int(int n);
void push_float(float n);
void push_obj(Object obj);

int equal_bytes(char *addr1, char *addr2, int tot);
int total_size(Object obj);

char* read_type(char type, char *ptr);
int parse_primitive_element(char *input, int start, char *ptr, char type);
int parse_struct_element(char *input, int start, char *ptr, char *struct_format);

void read_struct(Var *var, char *format);
void read_array(Var *var, char* format);
char* read_type(char type, char *ptr);


void write_struct(Object obj, char *format);
void write_array(Object obj, char *format);
int print_type(char type, char *ptr);

void exec_concat(int num, int size);

// Exec
void load_hcode();
void exec_vars(int num);
void exec_push(int n);
void exec_apop();
void exec_jump(int adress);
void exec_skip(int offset);
void exec_skpf(int offset); 
void exec_vall(int size, int num); 
void exec_loci(int value); 
void exec_locr(float value); 
void exec_locs(char *value); 
void exec_load(int env, int oid); 
void exec_grou(int num, int size, int card); 
void exec_loda(int env, int oid); 
void exec_inld(int offset, int size); 
void exec_cidx(); 
void exec_ixad(int scale); 
void exec_stor(); 
void exec_equa(); 
void exec_nequ(); 
void exec_addi();
void exec_addr(); 
void exec_subi(); 
void exec_subr(); 
void exec_muli();
void exec_mulr();
void exec_divi();
void exec_divr();
void exec_toin();
void exec_tore();
void exec_head();
void exec_card();
void exec_tail();
void exec_empt(); 
void exec_negi(); 
void exec_negr(); 
void exec_negb(); 
void exec_gthi(); 
void exec_geqi(); 
void exec_lthi(); 
void exec_leqi(); 
void exec_gthr(); 
void exec_geqr(); 
void exec_lthr(); 
void exec_leqr(); 
void exec_gths(); 
void exec_geqs(); 
void exec_lths(); 
void exec_leqs(); 
void exec_read(int oid, char *format); 
void exec_wrte(char *format); 
void exec_wrtl(char *format); 
void exec_retn();
void exec_blng(); 
void exec_rnge();