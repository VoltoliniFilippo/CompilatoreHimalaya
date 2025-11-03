#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "virtual_machine.h"

Hcode *prog;
int pc = 0;
int vp = 0;
int ap = 0;
int op = 0;
int ip = 0;
char istack[MAX_INSTANCES];
Var *vars;
Activation astack[MAX_ACTIVATIONS];
Object ostack[MAX_OBJECTS];
int max_vars = 0;
int input_exhausted = 0;

void main(int argc, char *argv[]){
  Hcode *stat;
  load_hcode();
  while((stat = &prog[pc++])->op != HALT)
    execute(stat);
}

/**
 * Carica il codice hcode.
 */
void load_hcode(){
  Code *code = genCode();
  int size = code->head->args[0].ival;
  prog = malloc(size * (sizeof(Hcode)));
  int i = 0;

  for(Stat *stat = code->head; stat != NULL; stat = stat->next){
    prog[i].op = stat->op;
    prog[i].args[0] = stat->args[0];
    prog[i].args[1] = stat->args[1];
    prog[i].args[2] = stat->args[2];
    ++i;
  }
}

/**
 * Esegue un'istruzione hcode per volta in base all'operatore.
 */
void execute(Hcode *stat){ 
  switch(stat->op){
    case HCOD: break;
    case VARS: exec_vars(stat->args[0].ival); break;
    case PUSH: exec_push(stat->args[0].ival); break;
    case APOP: exec_apop(); break;
    case JUMP: exec_jump(stat->args[0].ival); break;
    case SKIP: exec_skip(stat->args[0].ival); break;
    case SKPF: exec_skpf(stat->args[0].ival); break;
    case VALL: exec_vall(stat->args[0].ival, stat->args[1].ival); break;
    case LOCI: exec_loci(stat->args[0].ival); break;
    case LOCR: exec_locr(stat->args[0].rval); break;
    case LOCS: exec_locs(stat->args[0].sval); break;
    case LOAD: exec_load(stat->args[0].ival, stat->args[1].ival); break;
    case GROU: exec_grou(stat->args[0].ival, stat->args[1].ival, stat->args[2].ival); break;
    case LODA: exec_loda(stat->args[0].ival, stat->args[1].ival); break;
    case INLD: exec_inld(stat->args[0].ival, stat->args[1].ival); break;
    case CIDX: exec_cidx(); break;
    case IXAD: exec_ixad(stat->args[0].ival); break;
    case STOR: exec_stor(); break;
    case EQUA: exec_equa(); break;
    case NEQU: exec_nequ(); break;
    case ADDI: exec_addi(); break;
    case ADDR: exec_addr(); break;
    case SUBI: exec_subi(); break;
    case SUBR: exec_subr(); break;
    case MULI: exec_muli(); break;
    case MULR: exec_mulr(); break;
    case DIVI: exec_divi(); break;
    case DIVR: exec_divr(); break;
    case TOIN: exec_toin(); break;
    case TORE: exec_tore(); break;
    case HEAD: exec_head(); break;
    case CARD: exec_card(); break;
    case TAIL: exec_tail(); break;
    case EMPT: exec_empt(); break;
    case NEGI: exec_negi(); break;
    case NEGR: exec_negr(); break;
    case NEGB: exec_negb(); break;
    case GTHI: exec_gthi(); break;
    case GEQI: exec_geqi(); break;
    case LTHI: exec_lthi(); break;
    case LEQI: exec_leqi(); break;
    case GTHR: exec_gthr(); break;
    case GEQR: exec_geqr(); break;
    case LTHR: exec_lthr(); break;
    case LEQR: exec_leqr(); break;
    case GTHS: exec_gths(); break;
    case GEQS: exec_geqs(); break;
    case LTHS: exec_lths(); break;
    case LEQS: exec_leqs(); break;
    case READ: exec_read(stat->args[0].ival, stat->args[1].sval); break;
    case WRTE: exec_wrte(stat->args[0].sval); break;
    case WRTL: exec_wrtl(stat->args[0].sval); break;
    case RETN: exec_retn(); break;
    case FUNC: break; // Istruzione che non viene eseguita: serve da cornice sintattica per la definizione di funzione nel programma H-code
    case BLNG: exec_blng(); break;
    case RNGE: exec_rnge(); break;
    default: error("%d: unknown H-code instruction", stat->op); break;
  }
}

/**
 * Esegue il pop di un intero.
 */
int pop_int(){ 
  int n;
  
  n = * (int *) &istack[ip - SIZE_INT];
  pop_obj();
  return n;
}

/**
 * Esegue il pop di un float.
 */
float pop_float(){
  float n;
  Object obj = ostack[op - 1];

  if(obj.size == SIZE_FLOAT)
    n = * (float *) &istack[ip - SIZE_FLOAT];
  else
    n = *(int *) &istack[ip - SIZE_INT];
  pop_obj();
  return n;
}

/**
 * Esegue il pop di un oggetto, se op <= 0 ritorna errore.
 */
Object pop_obj(){
  if(op-- == 0) 
    error("Pop from empty object stack");
  ip -= total_size(ostack[op]);
  return ostack[op];
} 

/**
 * Ritorna la grandezza totale di un oggetto.
 */
int total_size(Object obj){   
  return (obj.size * obj.num);
}

/**
 * Esegue il push di un oggetto, se op == numero massimo di oggetti ritorna errore.
 */
void push_obj(Object obj){   
  if(op == MAX_OBJECTS) error("Object stack overflow");
  ostack[op++] = obj;
}

/**
 * Esegue il push di un intero.
 */
void push_int(int n){
  Object obj;

  obj.size = SIZE_INT;
  obj.num = 1;
  obj.var_index = -1;
  obj.addr = &istack[ip];
  * (int *) obj.addr = n;
  ip += SIZE_INT;
  push_obj(obj);
}

/**
 * Esegue il push di un float.
 */
void push_float(float n){
  Object obj;

  obj.size = SIZE_FLOAT;
  obj.num = 1;
  obj.var_index = -1;
  obj.addr = &istack[ip];
  * (float *) obj.addr = n;
  ip += SIZE_FLOAT;
  push_obj(obj);
}

/**
 * Confronta byte per byte due blocchi di memoria per verificare se sono identici.
 */
int equal_bytes(char *addr1, char *addr2, int tot){ 
  for(int i=0; i < tot; i++)
    if(addr1[i] != addr2[i])
      return 0;
  return 1;
}

/**
 * Stampa un errore e termina l'esecuzione del programma.
 */
void error(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "Errore: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  va_end(args);

  // Termina il programma
  exit(EXIT_FAILURE);
}