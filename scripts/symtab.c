#include "def.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

SymbolTableEntry *symtab[TOT];
SymbolTableEntry* scope_stack[MAX_SCOPE_DEPTH];
int param_counter = 0;
int var_counter = 0;
int func_counter = 1;
int scope_level = 0;

int hash(char *id)
{
    int h = 0;
    
    for(int i=0; id[i] != '\0'; i++)
        h = ((h<<SHIFT) + id[i]) % TOT;
    
    return h;
}

SymbolTableEntry* lookup_symbol(char* name) 
{
    int h = hash(name);
    SymbolTableEntry* sym = symtab[h];
    
    while (sym != NULL) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
        
        sym = sym->next;
    }
    return NULL;
}

SymbolTableEntry* lookup_local(char* name)
{
    if(scope_level > 0){
        SymbolTableEntry* sym = scope_stack[scope_level - 1];
        while (sym != NULL) {
            if (strcmp(sym->name, name) == 0) {
                return sym;
            }
            sym = sym->next;
        }
    }

    return NULL;
}

SymbolTableEntry* insert_symbol(char *name, Class class, Type *type) {
    int h = hash(name);
    
    // Controlla se il simbolo esiste già (solo per la tabella globale)
    if (class != PARAM_CLASS) {
        SymbolTableEntry* existing = lookup_symbol(name);
        if (existing != NULL) {
            return NULL; // Simbolo già esistente
        }
    }
    
    SymbolTableEntry* sym = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    if (sym == NULL) return NULL;
    
    sym->name = strdup(name);
    sym->class = class;
    sym->type = type;
    sym->formals = NULL;
    
    // Assegna OID
    if (class == FUNC_CLASS) 
        sym->oid = func_counter++;
    else if(class == VAR_CLASS)
        sym->oid = var_counter++;
    else if(class == PARAM_CLASS)
        sym->oid = param_counter++;
    else // TYPE_CLASS
        sym->oid = -1;
    
    // Gestione diversa per parametri vs altri simboli
    if (class == PARAM_CLASS) {
        // Aggiungi solo allo scope locale se siamo in uno scope
        if (scope_level > 0) {
            SymbolTableEntry* local_sym = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
            *local_sym = *sym;  // Copia
            local_sym->next = scope_stack[scope_level - 1];
            scope_stack[scope_level - 1] = local_sym;
        }
    }else if(class == FUNC_CLASS){
        // Crea una lista dei parametri dallo scope corrente
        SymbolTableEntry *param_list = NULL;
        SymbolTableEntry *last_param = NULL;
        
        // Scorri tutti i parametri nello scope corrente
        SymbolTableEntry *current_scope = scope_stack[scope_level - 1];
        
        while (current_scope != NULL) {
            if (current_scope->class == PARAM_CLASS) {
                // Crea una copia del parametro per la lista dei formals
                SymbolTableEntry *param_copy = malloc(sizeof(SymbolTableEntry));
                memcpy(param_copy, current_scope, sizeof(SymbolTableEntry));
                
                // Duplica anche il nome per evitare problemi di memoria
                param_copy->name = strdup(current_scope->name);
                param_copy->next = NULL;
                
                // Aggiungi alla lista dei formals
                if (param_list == NULL) {
                    param_list = param_copy;
                    last_param = param_copy;
                } else {
                    last_param->next = param_copy;
                    last_param = param_copy;
                }
            }
            current_scope = current_scope->next;
        }
        
        // Assegna la lista dei parametri alla funzione
        sym->formals = param_list;

        // Inserimento nella symbol table globale
        sym->next = symtab[h];
        symtab[h] = sym;        
    }else {
        // Inserimento nella symbol table globale
        sym->next = symtab[h];
        symtab[h] = sym;
    }
    
    return sym;
}

int count_vars(){
    int count = 0;

    for (int i = 0; i < TOT; i++) {
        SymbolTableEntry* sym = symtab[i];
        while (sym != NULL) {
            if(sym->class == VAR_CLASS)
                count++;
            sym = sym->next;
        }
    }

    return count;
}

SymbolTableEntry *get_vars(){
    int index = 0;
    int size = count_vars();
    SymbolTableEntry *vars = malloc(size * sizeof(SymbolTableEntry));

    for (int i = 0; i < TOT; i++) {
        SymbolTableEntry* sym = symtab[i];
        while (sym != NULL) {
            if(sym->class == VAR_CLASS)
                vars[index++] = *sym;
            sym = sym->next;
        }
    }

    return vars;
}

Type* create_type(Domain domain)
{
    Type* type = (Type*)malloc(sizeof(Type));
    type->domain = domain;
    type->child = NULL;
    type->fields = NULL;

    return type;
}

Type* create_vector_type(Domain *child, Field *fields)
{
    Type *vector_type = create_type(VECT_DOMAIN);
    vector_type->child = child;
    vector_type->fields = fields;

    return vector_type;
}

Type* create_struct_type(Field* fields)
{
    Type* struct_type = create_type(STRUCT_DOMAIN);
    struct_type->fields = fields;
    return struct_type;
}

void enter_scope()
{
    if(scope_level < MAX_SCOPE_DEPTH){
        scope_stack[scope_level] = NULL;
        scope_level++;
    }
}

void exit_scope()
{
    if(scope_level > 0){
        scope_level--;
        SymbolTableEntry* sym = scope_stack[scope_level];
        while (sym != NULL) {
            SymbolTableEntry* temp = sym;
            sym = sym->next;
            free(temp->name);
            free(temp);
        }
    }
}

void print_error(char* msg, char* name)
{
    fprintf(stderr, "Errore: %s '%s'\n", msg, name);
}

void print_symbol_table()
{
    printf("Symbol Table:\n");
    for (int i = 0; i < TOT; i++) {
        SymbolTableEntry* sym = symtab[i];
        while (sym != NULL) {
            // Controlla se sym->name è valido
            if (sym->name != NULL) {
                printf("Name: %s, Class: %d, OID: %d", sym->name, sym->class, sym->oid);
            } else {
                printf("Name: NULL, Class: %d, OID: %d", sym->class, sym->oid);
            }
            
            // Controlla se type è valido
            if (sym->type != NULL) {
                printf(", Type: %d\n", sym->type->domain);
            } else {
                printf(", Type: NULL\n");
            }
            
            if(sym->class == FUNC_CLASS && sym->formals != NULL){
                printf("Formals:\n");
                for(SymbolTableEntry *formal = sym->formals; formal != NULL; formal = formal->next) {
                    if (formal->name != NULL) {
                        printf("Name: %s, Class: %d, OID: %d", formal->name, formal->class, formal->oid);
                    } else {
                        printf("Name: NULL, Class: %d, OID: %d", formal->class, formal->oid);
                    }
                    
                    if (formal->type != NULL) {
                        printf(", Type: %d\n", formal->type->domain);
                    } else {
                        printf(", Type: NULL\n");
                    }
                }

                printf("End Formals\n");
            }

            sym = sym->next;
        }
    }
}