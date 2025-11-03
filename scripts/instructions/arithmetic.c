#include "virtual_machine.h"


/**
 * Sostituisce i due numeri interi su ostack con il risultato della loro somma.
 */
void exec_addi(){ 
  int n, m;
  
  n = pop_int();
  m = pop_int();
  push_int(m + n);
}

/**
 * Sostituisce i due numeri reali su ostack con il risultato della loro somma.
 */
void exec_addr(){
  float n, m;

  n = pop_float();
  m = pop_float();
  push_float(m + n);
}

/**
 * Sostituisce i due numeri interi su ostack con la loro differenza.
 */
void exec_subi(){ 
  int n, m;
  
  n = pop_int();
  m = pop_int();
  push_int(m - n);
}

/**
 * Sostituisce i due numeri reali su ostack con la loro differenza.
 */
void exec_subr(){
  float n, m;

  n = pop_float();
  m = pop_float();
  push_float(m - n);
}

/**
 * Sostituisce i due numeri interi su ostack con il risultato della loro moltiplicazione.
 */
void exec_muli(){ 
  int n, m;
  
  n = pop_int();
  m = pop_int();
  push_int(m * n);
}

/**
 * Sostituisce i due numeri interi su ostack con il risultato della loro moltiplicazione.
 */
void exec_mulr(){
  float n, m;

  n = pop_float();
  m = pop_float();
  push_float(m * n);
}

/**
 * Sostituisce i due numeri interi su ostack con il risultato (intero) della loro divisione.
 */
void exec_divi(){ 
  int n, m;
  
  n = pop_int();
  m = pop_int();
  push_int(m / n);
}

/**
 * Sostituisce i due numeri reali su ostack con il risultato (intero) della loro divisione.
 */
void exec_divr(){
  float n, m;

  n = pop_float();
  m = pop_float();
  push_float(m / n);
}