#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "virtual_machine.h"

/**
 * Assegna il valore della variabile oid leggendolo dinamicamente (nel formato format) dallo standard input.
 */
void exec_read(int oid, char *format){
  Var *var = &vars[oid];

  if (feof(stdin) && !input_exhausted) {
    clearerr(stdin);  // Pulisce il flag EOF
    
    #ifdef _WIN32
      freopen("CON", "r", stdin);
    #else
      freopen("/dev/tty", "r", stdin);
    #endif
    
    input_exhausted = 1;
  }
  
  if(strcmp(format, "\"i\"") == 0)
    scanf(" %d", (int*)var->addr);
  else if (strcmp(format, "\"r\"") == 0)
    scanf(" %f", (float*)var->addr);
  else if (strcmp(format, "\"s\"") == 0) {
    char buffer[1024];
    scanf(" %1023s", buffer);
    int len = strlen(buffer);
    
    // Controlla se dobbiamo allocare o riallocare
    if(var->addr == NULL) {
        var->addr = malloc(len + 1);
    } else {
        var->addr = realloc(var->addr, len + 1);
    }
    strcpy((char*)var->addr, buffer);
  }
  else if (strcmp(format, "\"b\"") == 0) //DA CONTROLLARE
    scanf(" %d", (int*)var->addr);
  else if (format[1] == '{')
    read_struct(var, format);
  else if (format[1] == '[')
    read_array(var, format);
  else 
    error("Unknown read format: %s", format);
}

/**
 * Legge una struttura dallo standard input.
 */
void read_struct(Var *var, char *format){
  char *ptr = var->addr;

  for(int i = 1; format[i] != '}'; i++){
    if(format[i] == ':'){
      int j;
      for(j = i + 1; format[j] == ' '; j++)

      ptr = read_type(format[j], ptr);
    }

    while(format[i] != ',' && format[i] != '}') i++;
    
    if(format[i] == ','){
      while(format[i+1] == ' ') i++;
    }
  }
}

char* read_type(char type, char *ptr){
  switch(type){
    case 's':
      scanf("%s", ptr);
      ptr += strlen(ptr) + 1;
      break;
  
    case 'i':
      scanf("%d", (int*)ptr);
      ptr += sizeof(int);
      break;
    
    case 'r':
      scanf("%f", (float*)ptr);
      ptr += sizeof(float);
      break;

    case 'b':
      int temp;
      scanf("%d", &temp);
      *(int*)ptr = temp;
      ptr += sizeof(int);
      break;

    default:
      error("Unknown type: %c", type);
  }

  return ptr;
}

/**
 * Legge un array dallo standard input.
 */
void read_array(Var *var, char* format){
  char elem_format[256];
  int len = strlen(format);

  for(int i = 1; format[i] != ']'; i++) 
    elem_format[len++] = format[i];

  elem_format[len] = '\0';

  int count = 0;
  if (len > 2) {
    count = 1;
    for(int i = 1; i < len-1; i++) {
      if (format[i] == ',') 
        count++;
    }
  }

  if (var->addr) free(var->addr);
  var->num = count;
  var->addr = malloc(var->size * count);

  //Array vuoto
  if (count == 0) return;

  char *ptr = var->addr;
  int pos = 1;
    
  for(int elem = 0; elem < count; elem++) {
    // Salta spazi
    while(pos < len && format[pos] == ' ') pos++;
      
    if (elem_format[0] == '{') {
      // Elemento è una struttura
      pos = parse_struct_element(format, pos, ptr, elem_format);
    } else {
      // Elemento è un tipo primitivo
      pos = parse_primitive_element(format, pos, ptr, elem_format[0]);
    }
      
    ptr += var->size;
      
    // Salta virgola e spazi
    while(pos < len && (format[pos] == ',' || format[pos] == ' ')) pos++;
  }
}

/**
 * Estrae un valore primitivo da una stringa di input a partire da una posizione specifica e lo converte nel tipo appropriato, ritorna la posizione in cui si è fermato.
 */
int parse_primitive_element(char *input, int start, char *ptr, char type){
    int pos = start;
    char temp[256];
    int temp_pos = 0;
    
    // Estrae valore fino a virgola o ']'
    while(pos < strlen(input) && input[pos] != ',' && input[pos] != ']' && input[pos] != ' ')
      temp[temp_pos++] = input[pos++];

    temp[temp_pos] = '\0';
    
    // Converti in base al tipo
    switch(type) {
      case 'i':
        *(int*)ptr = atoi(temp);
        break;
      case 'r':
        *(float*)ptr = atof(temp);
        break;
      case 'b':
        *(int*)ptr = (strcmp(temp, "true") == 0 || strcmp(temp, "1") == 0) ? 1 : 0;
        break;
      case 's':
        if (temp[0] == '"' && temp[temp_pos-1] == '"') {
            temp[temp_pos-1] = '\0';  // Rimuovi il " finale
            strcpy(ptr, temp + 1);    // Copia senza il " iniziale
        } else {
            strcpy(ptr, temp);
        }
        break;
    }
    
    return pos;
}

int parse_struct_element(char *input, int start, char *ptr, char *struct_format){
  int pos = start;
  
  // Salta fino a '{'
  while(pos < strlen(input) && input[pos] != '{') pos++;
  if (input[pos] != '{') {
    error("Per gli elementi di tipo struttura era atteso un '{' all'inizio dell'input");
    return pos;
  }
  pos++;  // Salta '{'
  
  // Parsing della struttura usando il formato
  char *struct_ptr = ptr;
  
  for(int i = 1; struct_format[i] != '}'; i++) {
    if(struct_format[i] == ':') {
      // Salta fino al prossimo campo nell'input
      while(pos < strlen(input) && input[pos] != ':') pos++;
      pos++;  // Salta ':'
  
      // Salta spazi
      while(pos < strlen(input) && input[pos] == ' ') pos++;
      
      // Trova il tipo nel formato
      int j;
      for(j = i + 1; struct_format[j] == ' '; j++);
      char type = struct_format[j];
      
      // Parsing del valore
      pos = parse_primitive_element(input, pos, struct_ptr, type);
      
      // Aggiorna puntatore struttura
      switch(type) {
        case 's':
          struct_ptr += strlen(struct_ptr) + 1;
          break;
        case 'i':
        case 'b':
          struct_ptr += sizeof(int);
          break;
        case 'r':
          struct_ptr += sizeof(float);
          break;
      }
      
      // Salta nel formato fino a ',' o '}'
      while(struct_format[i] != ',' && struct_format[i] != '}') i++;
      if(struct_format[i] == ',') {
        // Nell'input, salta fino alla prossima virgola
        while(pos < strlen(input) && input[pos] != ',' && input[pos] != '}') pos++;
        if(input[pos] == ',') pos++;
      }
    }
  }
  
  // Salta fino a '}'
  while(pos < strlen(input) && input[pos] != '}') pos++;
  if(input[pos] == '}') pos++;
  
  return pos;
}

/**
 * Stampa sullo standard output, nel formato format, l'istanza dell'oggetto in cima ad ostack; quindi, fa il pop di ostack.
 */
void exec_wrte(char *format){
  Object obj = pop_obj();

  if(strcmp(format, "\"i\"") == 0)
    printf("%d", *(int*)obj.addr);
  else if(strcmp(format, "\"r\"") == 0)
    printf("%f", *(float*)obj.addr);
  else if(strcmp(format, "\"s\"") == 0)
    printf("%s", (char*)obj.addr);
  else if (strcmp(format, "\"b\"") == 0)
    printf("%s", *(int*)obj.addr ? "true" : "false");
  else if (format[1] == '{')
    write_struct(obj, format);
  else if (format[1] == '[')
    write_array(obj, format);
  else
    error("Unknown write format: %s", format);
}

int print_type(char type, char *ptr){
  if(type == 's') {
    printf("\"%s\"", ptr);
    return strlen(ptr) + 1;
  } else if(type == 'i') {
    printf("%d", *(int*)ptr);
    return sizeof(int);
  } else if(type == 'r') {
    printf("%.2f", *(float*)ptr);
    return sizeof(float);
  } else if(type == 'b') {
    printf("%s", *(int*)ptr ? "true" : "false");
    return sizeof(int);
  }
}

int get_type_str_size(char str){
  if(str == 'b' || str == 'i')
    return sizeof(int);
  else if(str == 'r')
    return sizeof(float);
  else  
    return sizeof(char*);
}

/**
 * Stampa sullo standard output una struttura.
 */
void write_struct(Object obj, char *format) {
  char *ptr = obj.addr;
  int count = 0;

  printf("{");
  
  for(int i = 0; i < strlen(format); i++) {    
    char type_char = format[i];

    if(type_char == 's' || type_char == 'b' || type_char == 'i' || type_char == 'r'){
      if(count != 0)  
        printf(", ");

      int size = get_type_str_size(type_char);
      print_type(type_char, ptr);
      ptr += size;
      count++;
    }
  }
  
  printf("}");
}

/**
 * Stampa sullo standard output un array.
 */
void write_array(Object obj, char *format){
  char *ptr = obj.addr;
  char *type = format[2];
  int count = 0;

  for(int i = 0; i < total_size(obj); i += obj.size)
    ++count;

  // Nel caso in cui l'elemento sia unico (ad esempio quando viene effettuato un indexing, lo stampo singolarmente)
  if(count == 1){
    print_type(type, ptr);
  }
  // Altrimenti stampo i valori di un array compreso tra []
  else{
    printf("[");
    for(int i = 0; i < total_size(obj); i += obj.size){
      if(i != 0)
        printf(", ");
      print_type(type, ptr+i);
    }
    printf("]");
  }

  /*for(int i = 2; format[i] != ']'; i++){
    char type = format[i];

    if(format[i] != ',' && format[i] != ' ')
      ptr += print_type(format[i], ptr);
  }*/
}

/**
 * Stampa sullo standard output, nel formato format, l'istanza dell'oggetto in cima ad ostack aggiungendo un newline; 
 * quindi, fa il pop di ostack.
 */
void exec_wrtl(char *format){
  exec_wrte(format);
  printf("\n");
}