#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "virtual_machine.h"

/**
 * Alloca in vars[vp++] un oggetto in cui: size = size, num = num. Se num > 0, alloca nello heap 
 * una stringa di byte di lunghezza size * num e ne assegna il puntatore al campo addr del descrittore; 
 * altrimenti (se num = 0), addr = NULL.
 */
void exec_vall(int size, int num){
  //fprintf(stderr, "exec_vall called: vp=%d, max_vars=%d, size=%d, num=%d\n", vp, max_vars, size, num);
  if(vp >= max_vars)
    error("Var array overflow");
  
  Var *var = &vars[vp++];
  var->size = size;
  var->num = num;

  if(num > 0){
    var->addr = malloc(size * num);

    if(!var->addr)
      error("Memory allocation failed");
  }else{
    var->addr = NULL;
  }
}

/**
 * Carica su ostack un numero intero di valore intconst.
 */
void exec_loci(int value){
  push_int(value);
}

/**
 * Carica su ostack un numero reale di valore realconst.
 */
void exec_locr(float value){
  push_float(value);
}

/**
 * Carica su ostack il puntatore (unico per stringhe uguali) ad una stringa di valore strconst.
 */
void exec_locs(char *value){
  Object obj;

  obj.num = 1;
  obj.size = sizeof(char*);
  obj.addr = &istack[ip];

  //Copio la stringa sull'istack
  strcpy((char*)obj.addr, value);
  
  ip += obj.size;

  if(ip > MAX_INSTANCES)
    error("instance overflow in exec_locs");

  push_obj(obj);
}


/**
 * Carica su ostack il valore dell'oggetto identificato da oid nell'ambiente (variabile se env = 0, parametro se env = 1).
 */
void exec_load(int env, int oid){
  Object obj;

  if(env == 0){
    Var *var = &vars[oid];
    obj.size = var->size;
    obj.num = var->num;
    obj.addr = &istack[ip];

    memcpy(obj.addr, var->addr, obj.size * obj.num);
  }else{
    int param_index = astack[ap - 1].objs + oid;

    if (param_index >= op)
      error("Parameter index out of bounds: %d (op=%d)", param_index, op);

    obj = ostack[param_index];
    
    // Crea una copia del parametro sull'istack
    Object copy;
    copy.size = obj.size;
    copy.num = obj.num;
    copy.addr = &istack[ip];
    memcpy(copy.addr, obj.addr, total_size(obj));
    obj = copy;
  }

  push_obj(obj);
  ip += total_size(obj);
}

/**
 * Concatena in un unico vettore il valore dei due elementi presenti sulla cima dell'ostack, siano essi vettori o elementi singoli.
 */
void exec_concat(int num, int size){
  Object result;
  result.size = size;

  Object obj2 = pop_obj();
  Object obj1 = pop_obj();

  result.num = obj1.num + obj2.num;
  result.addr = &istack[ip];

  memcpy(result.addr, obj1.addr, total_size(obj1));
  memcpy(result.addr + total_size(obj1), obj2.addr, total_size(obj2));

  push_obj(result);
  ip += total_size(result);
}

/**
 * Sostituisce num oggetti su ostack con un oggetto il cui valore (puntato da addr) è la concatenazione dei valori degli oggetti (campi di struttura o elementi di vettore), 
 * assegnando size = size e num = card nel descrittore dell'oggetto risultante.
 */
void exec_grou(int num, int size, int card){
  if(card == -1)
    return exec_concat(num, size);

  int offset = 0;
  
  // Crea un array temporaneo per memorizzare gli oggetti nello stack
  Object *temp = malloc(num * sizeof(Object));
  
  // Pop degli oggetti nell'array temporaneo
  for(int i = 0; i < num; i++)
    temp[i] = pop_obj();
  
  Object result;
  result.size = size;
  result.num = card;
  result.addr = &istack[ip];

  // Copia gli oggetti nell'ordine inverso (dal primo all'ultimo)
  for(int i = num - 1; i >= 0; i--){
    int obj_size = total_size(temp[i]);
    memcpy(result.addr + offset, temp[i].addr, obj_size);
    offset += obj_size;
  }
  
  free(temp); // Libera la memoria temporanea

  push_obj(result);
  ip += offset;
}

/**
 * Carica su ostack una copia del descrittore dell'oggetto identificato da oid nell'ambiente (variabile se env = 0, parametro 
 * se env = 1) : tutti i campi della copia del descrittore (compreso addr) mantengono lo stesso valore.
 */
void exec_loda(int env, int oid){
  Object obj;

  if(env == 0){
    Var *var = &vars[oid];
    obj.size = var->size;
    obj.num = var->num;
    obj.addr = var->addr;
    obj.var_index = oid;
    ip += obj.size * obj.num;
  }else{
    int param_index = astack[ap - 1].objs + oid;
    obj = ostack[param_index];
    obj.var_index = -1;
  }

  push_obj(obj);
}


/**
 * Assegna il valore all'indirizzo addr dell'oggetto sotto la cima di ostack con con il valore dell'oggetto in cima ad ostack; 
 * quindi, fa il pop di entrambi gli oggetti su ostack. Se la dimensione (num * size) del valore da assegnare è diversa da 
 * quella dell'oggetto sotto la cima di ostack (caso di vettore), il vecchio valore (puntato da addr) viene deallocato ed un 
 * nuovo valore viene allocato con un numero di byte pari alla dimensione del valore dell'oggetto in cima ad ostack.
 */
void exec_stor(){
  Object value = ostack[op - 1];
  Object target = ostack[op - 2];
  
  int value_size = total_size(value);
  int target_size = total_size(target);
  
  // caso in cui l'oggetto target sia una variabile
  if(target.var_index >= 0){
    if(value_size == target_size){
      memcpy(vars[target.var_index].addr, value.addr, value_size);
    }else{  
      free(target.addr);
      vars[target.var_index].num = value.num;
      vars[target.var_index].addr = malloc(value_size);
      memcpy(vars[target.var_index].addr, value.addr, value_size);
    }
  }else{
    target.addr = malloc(value_size);
    memcpy(target.addr, value.addr, value_size);
  }

  // Pop di entrambi gli oggetti
  pop_obj();
  pop_obj();
}

/**
 * Sostituisce l'oggetto in cima ad ostack (con campo addr) con un oggetto il cui valore (di dimensione size) è una copia 
 * del valore che inizia all'indirizzo addr + offset. Assegna size = size e num = 1 nel descrittore dell'oggetto risultante.
 */
void exec_inld(int offset, int size){
  Object obj = pop_obj();
  Object result;

  result.size = size;
  result.num = 1;
  result.addr = &istack[ip];
  memcpy(result.addr, obj.addr + offset, size);
  ip += size;
  push_obj(result);
}

/**
 * Controlla che l'indice in cima a ostack sia nel range [0..num-1], in cui num è la cardinalità del vettore sotto la cima di ostack. 
 * In caso contrario, stampa un messaggio di errore e termina l'esecuzione del programma.
 */
void exec_cidx(){
  Object index_obj = ostack[op - 1];
  Object obj = ostack[op - 2];
  int index = *(int*)index_obj.addr;

  if(index < 0 || index >= obj.num)
    error("Array index out of bounds: %d not in [0..%d]", index, obj.num-1);
}

/**
 * Fa il pop del valore intero val (indice di vettore o offset di campo) in cima a ostack e incrementa addr dell'oggetto 
 * sottostante (ora in cima a ostack): addr += val * scale (i campi size e num nel descrittore non sono rilevanti).
 */
void exec_ixad(int scale){
  int val = pop_int();
  Object obj = pop_obj();
  obj.addr += val * scale;
  push_obj(obj);
}

/**
 * Sostituisce i due numeri interi su ostack con il vettore di interi definito dal range delimitato dai due numeri interi.
 */
void exec_rnge(){
  int end = pop_int();
  int start = pop_int();

  int count = end - start + 1;
  if(count < 0)
    count = 0;

  Object range;
  range.size = SIZE_INT;
  range.num = count;
  range.addr = &istack[ip];

  for(int i = 0; i < count; i++)
    *((int*)(range.addr + i * SIZE_INT)) = start + i;

  ip += count * SIZE_INT;
  push_obj(range);
}

/**
 * Alloca il vettore vars (memoria delle variabili globali), di dimensione num.
 */
void exec_vars(int num){
  if (vars != NULL) {
    for (int i = 0; i < vp; i++) {
      if (vars[i].addr != NULL) 
        free(vars[i].addr);
    }
    
    free(vars);
  }
  
  vars = malloc(num * sizeof(Var));
  if (!vars) {
    error("Memory allocation failed for vars array");
  }

  for (int i = 0; i < num; i++) {
    vars[i].addr = NULL;
    vars[i].size = 0;
    vars[i].num = 0;
  }

  max_vars = num;
  vp = 0;
}