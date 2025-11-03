#include <string.h>
#include <stdio.h>
#include "virtual_machine.h"

/**
 * Sostituisce il numero (intero) in cima ad ostack con il numero reale risultante dalla operazione di cast (da intero a reale).
 */
void exec_tore(){
  int n;

  n = pop_int();
  push_float((float) n);
}

/**
 * Sostituisce il numero (reale) in cima ad ostack con il numero intero risultante dalla operazione di cast (da reale a intero).
 */
void exec_toin(){
  float n;

  n = pop_float();
  push_int((int) n);
}

/**
 * Sostituisce il vettore in cima ad ostack con un valore booleano (intero) che indica se il vettore è vuoto.
 */
void exec_empt(){
  Object vect;
  vect = pop_obj();

  push_int(vect.num == 0);
}

/**
 * Sostituisce il vettore in cima ad ostack con il primo elemento (testa) del vettore. 
 * In caso di vettore vuoto, stampa un messaggio di errore e termina l'esecuzione.
 */
void exec_head(){
  Object vect;
  
  vect = pop_obj();
  if(vect.size == 0)
    error("Vector is empty!");
  
  Object head;
  head.size = vect.size;
  head.num = 1;
  head.addr = &istack[ip];
  memcpy(head.addr, vect.addr, vect.size);
  ip += vect.size;
  push_obj(head);
}

/**
 * Sostituisce il vettore in cima ad ostack con la coda del vettore (gli elementi dopo la testa). 
 * In caso di vettore vuoto, stampa un messaggio di errore e termina l'esecuzione.
 */
void exec_tail(){
  Object vect = pop_obj();

  if(vect.size == 0)
    error("Vector is empty!");

  Object tail;
  tail.size = vect.size;
  tail.num = vect.num - 1;
  tail.addr = &istack[ip];

  if(tail.num > 0){
    memcpy(tail.addr, vect.addr + tail.size, tail.num * vect.size);
    ip += tail.num * vect.size;
  }

  push_obj(tail);
}

/**
 * Sostituisce il vettore in cima ad ostack con la sua cardinalità.
 */
void exec_card(){
  Object vect;
  vect = pop_obj();
  push_int(vect.num);
}