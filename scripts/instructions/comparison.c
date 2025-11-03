#include "virtual_machine.h"
#include <string.h>

/**
 * Sostituisce i due numeri interi su ostack con il booleano (intero) risultante dalla operazione di confronto >.
 */
void exec_gthi(){
  int n1, n2;

  n2 = pop_int();
  n1 = pop_int();
  push_int(n1 > n2);
}

/**
 * Sostituisce i due numeri reali su ostack con il booleano (intero) risultante dalla operazione di confronto >.
 */
void exec_gthr(){
  float n1, n2;

  n2 = pop_float();
  n1 = pop_float();
  push_int(n1 > n2);
}

/**
 * Sostituisce le due stringhe (puntatori)  su ostack con il booleano (intero) risultante dalla operazione di confronto >.
 */
void exec_gths(){
  Object obj2 = pop_obj();
  Object obj1 = pop_obj();

  char *str1 = obj1.addr;
  char *str2 = obj2.addr;

  push_int(strcmp(str1, str2) > 0);
}

/**
 * Sostituisce i due interi su ostack con il booleano (intero) risultante dalla operazione di confronto <.
 */
void exec_lthi(){
  int n1, n2;

  n2 = pop_int();
  n1 = pop_int();
  push_int(n1 < n2);
}

/**
 * Sostituisce i due reali su ostack con il booleano (intero) risultante dalla operazione di confronto <.
 */
void exec_lthr(){
  int n1, n2;

  n2 = pop_float();
  n1 = pop_float();
  push_int(n1 < n2);
}

/**
 * Sostituisce le due stringhe (puntatori) su ostack con il booleano (intero) risultante dalla operazione di confronto <.
 */
void exec_lths(){
  Object obj2 = pop_obj();
  Object obj1 = pop_obj();

  char *str1 = obj1.addr;
  char *str2 = obj2.addr;

  push_int(strcmp(str1, str2) < 0);
}


/**
 *  Sostituisce i due numeri interi su ostack con il booleano (intero) risultante dalla operazione di confronto ≥.
 */
void exec_geqi(){
  int n1, n2;

  n2 = pop_int();
  n1 = pop_int();
  push_int(n1 >= n2);
}

/**
 * Sostituisce i due numeri reali su ostack con il booleano (intero) risultante dalla operazione di confronto ≥.
 */
void exec_geqr(){
  float n1, n2;

  n2 = pop_float();
  n1 = pop_float();
  push_int(n1 >= n2);
}

/**
 * Sostituisce le due stringhe (puntatori) su ostack con il booleano (intero) risultante dalla operazione di confronto ≥.
 */
void exec_geqs(){
  Object obj2 = pop_obj();
  Object obj1 = pop_obj();

  char *str1 = obj1.addr;
  char *str2 = obj2.addr;

  push_int(strcmp(str1, str2) >= 0);
}

/**
 * Sostituisce i due interi su ostack con il booleano (intero) risultante dalla operazione di confronto ≤.
 */
void exec_leqi(){
  int n1, n2;

  n2 = pop_int();
  n1 = pop_int();
  push_int(n1 <= n2);
}

/**
 * Sostituisce i due reali su ostack con il booleano (intero) risultante dalla operazione di confronto ≤.
 */
void exec_leqr(){
  float n1, n2;

  n2 = pop_float();
  n1 = pop_float();
  push_int(n1 <= n2);
}

/**
 * Sostituisce le due stringhe (puntatori) su ostack con il booleano (intero) risultante dalla operazione di confronto ≤.
 */
void exec_leqs(){
  Object obj2 = pop_obj();
  Object obj1 = pop_obj();

  char *str1 = obj1.addr;
  char *str2 = obj2.addr;

  push_int(strcmp(str1, str2) <= 0);
}

/**
 * Sostituisce il vettore in cima ad ostack e l'elemento sotto la cima con un valore booleano (intero) 
 * che indica se l'elemento appartiene al vettore.
 */
void exec_blng(){
  Object vector = pop_obj();
  Object element = pop_obj();

  int found = 0;

  for(int i = 0; i < vector.num; i++){
    char *element_addr = vector.addr + i * vector.size;

    if(total_size(element) == vector.size && equal_bytes(element.addr, element_addr, vector.size)){
      found = 1;
      break;
    }
  }

  push_int(found);
}