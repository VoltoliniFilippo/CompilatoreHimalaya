#include <stdlib.h>
#include <string.h>
#include "virtual_machine.h"

/**
 * Aggiorna il program counter: pc = entry.
 */
void exec_jump(int address){
  pc = address;
}

/**
 * Aggiorna pc += offset-1.
 */
void exec_skip(int offset){
  pc += offset-1;
}

/**
 * Se il booleano (intero) in cima ad ostack è 0, aggiorna pc += offset-1; esegue quindi in ogni caso il pop del booleano (intero) in cima ad ostack.
 */
void exec_skpf(int offset){
  if(!pop_int())
    pc += offset-1;
}

/**
 * Mette su astack un nuovo RA, in cui: num = n, objs = op - n, ret = pc+1.
 */
void exec_push(int n){
  if(ap >= MAX_ACTIVATIONS)
    error("Activation stack overflow");

  astack[ap].num = n;
  astack[ap].objs = op - n;
  astack[ap].ret = pc + 1;
  ap++;
}

/**
 * Esegue il pop di astack (cioè, effettua il decremento ap--).
 */
void exec_apop(){
  if(ap == 0)
    error("Pop from empty activation stack  ");
  ap--;
}

/**
 * Sostituisce i parametri attuali (sotto la cima di ostack) della funzione corrente in astack con l'oggetto in cima a ostack; 
 * quindi, aggiorna pc = astack[ap-1].ret.
 */
void exec_retn() {
  if(ap == 0)
    error("Return with empty activation stack");

  Object result = pop_obj();
  
  // Copia il risultato in un buffer temporaneo perché result.addr punta a una zona che verrà invalidata
  char *temp_buffer = malloc(total_size(result));
  memcpy(temp_buffer, result.addr, total_size(result));

  // Salva le informazioni del record di attivazione corrente
  int start_index = astack[ap-1].objs;
  int return_address = astack[ap-1].ret;
  
  // Calcola la dimensione totale degli oggetti da rimuovere
  int total_size_to_free = 0;
  for (int i = start_index; i < op; i++)
    total_size_to_free += total_size(ostack[i]);

  // Rimuovi gli oggetti dall'ostack
  op = start_index;
  
  // Libera lo spazio corrispondente sull'istack
  ip -= total_size_to_free;

  // Ripristina il program counter
  pc = return_address;

  // Pusha il risultato nella nuova posizione corretta
  result.addr = &istack[ip];
  memcpy(result.addr, temp_buffer, total_size(result));
  free(temp_buffer);
  
  push_obj(result);
  ip += total_size(result);
}