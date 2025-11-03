#include "virtual_machine.h"

/**
 * Sostituisce il numero intero num in cima ad ostack con - num (cambiamento di segno).
 */
void exec_negi(){
  int n;

  n = pop_int();
  push_int(-n);
}

/**
 * Sostituisce il numero reale num in cima ad ostack con - num (cambiamento di segno
 */
void exec_negr(){
  float n;

  n = pop_float();
  push_int(-n);
}

/**
 * Sostituisce il valore booleano (intero) in cima ad ostack con il valore negato (0 diventa 1 ed 1 diventa 0).
 */
void exec_negb(){
  int n;

  n = pop_int();
  push_int(!n);
}

/**
 * Sostituisce i due oggetti su ostack con il booleano (intero) risultante dalla operazione di uguaglianza. 
 */
void exec_equa(){ 
  Object obj1, obj2;
  int tot;
  obj2 = pop_obj(); 
  obj1 = pop_obj();
  push_int((tot = total_size(obj1)) == total_size(obj2) && equal_bytes(obj1.addr, obj2.addr, tot));
}

/**
 *  Sostituisce i due oggetti su ostack con il booleano (intero) risultante dalla operazione di disuguaglianza.
 */
void exec_nequ(){ 
  Object obj1, obj2;
  int tot;
  obj2 = pop_obj(); 
  obj1 = pop_obj();
  push_int(!((tot = total_size(obj1)) == total_size(obj2) && equal_bytes(obj1.addr, obj2.addr, tot)));
}