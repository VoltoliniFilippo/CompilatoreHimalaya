#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen.h"

/**
 * Rimuove gli apici da una stringa.
 */
char *remove_quotes(char *str){
    size_t len = strlen(str);
    char *newStr = malloc(len - 2);
    strcpy(newStr, str + 1);
    newStr[len-2] = '\0';

    return newStr;
}

/**
 * Ritorna il numero di elementi di un elemento della symbol table.
 */
int get_num_of_elements(SymbolTableEntry *entry){
    if(entry->type->domain != VECT_DOMAIN)
        return 1;
    
    if(entry->type->child == NULL)
        return 0; // DA SISTEMARE
    
}

/**
 * Costruisce e ritorna una stringa contenente due caratteri c1 e c2 rispettivamente all'inizio e alla fine della nuova stringa.
 */
char *construct_str(char *str, char c1, char c2){
    size_t len = strlen(str);
    char *newStr = malloc(len + 3);
    newStr[0] = c1;
    strcpy(newStr + 1, str);
    newStr[len + 1] = c2;
    newStr[len + 2] = '\0';

    return newStr;
}

/**
 * Ritorna un tipo in formato stringa per la generazione di codice.
 */
char *get_format(Type *type){
    char *domain = get_type_str(type);
    char *quoted = construct_str(domain, '\"', '\"');

    return quoted;
}

/**
 * Ritorna una stringa che va ad identificare il tipo passato per parametro.
 */
char *get_type_str(Type *type){
    switch(type->domain){
        case BOOLEAN_DOMAIN:
            return "b";

        case INTEGER_DOMAIN:
            return "i";

        case REAL_DOMAIN:
            return "r";

        case STRING_DOMAIN:
            return "s";

        case VECT_DOMAIN:
            return get_format_vect(type);
            
        case STRUCT_DOMAIN:
            return get_format_struct(type);
        
        default:
            print_error("Tipo non riconosciuto", "");
            return NULL;
    }
}

/**
 * Ritorna una stringa che vad ad identificare il dominio passato per parametro.
 */
char *get_domain_str(Domain domain){
    switch(domain){
        case BOOLEAN_DOMAIN:
            return "b";

        case INTEGER_DOMAIN:
            return "i";

        case REAL_DOMAIN:
            return "r";

        case STRING_DOMAIN:
            return "s";
    }
}

/**
 * Ritorna una stringa che contiene il formato della struttura passata come parametro.
 */
char *get_format_struct(Type *type){
    size_t buffer_size = 256;
    char *str = malloc(buffer_size);

    for(Field *field = type->fields; field != NULL; field = field->next){
        char *domain = get_domain_str(field->domain);

        if (strlen(str) > 0)
            strcat(str, ",");

        strcat(str, domain);
    }

    return construct_str(str, '{', '}');
}

/**
 * Ritorna una stringa che contiene il formato del vettore passato come parametro.
 */
char *get_format_vect(Type *type){
    char *domain;
    if(*(type->child) == STRUCT_DOMAIN)
        domain = get_format_struct(type);
    else
        domain = get_domain_str(*(type->child));
    
    return construct_str(domain, '[', ']');
}

/**
 * Ritorna la dimensione di un tipo passato come parametro.
 */
int get_type_size(Type *type){
    if(type == NULL)
        return -1;

    switch(type->domain){
        case BOOLEAN_DOMAIN:
        case INTEGER_DOMAIN:
        case REAL_DOMAIN:
        case STRING_DOMAIN:
            return get_domain_size(type->domain);

        case VECT_DOMAIN:
            return get_vect_size(type);

        case STRUCT_DOMAIN:
            return get_struct_size(type);
    }
}

/**
 * Ritorna la dimensione di un vettore passato come parametro.
 */
int get_vect_size(Type *type){
    Domain child = *type->child;
    
    switch(child){
        case BOOLEAN_DOMAIN:
        case INTEGER_DOMAIN:
        case REAL_DOMAIN:
        case STRING_DOMAIN:
            return get_domain_size(child);

        case EMPTY_DOMAIN:
            return 0;

        case STRUCT_DOMAIN:
            return get_struct_size(type);

        default:
            return 0;
    }
}

/**
 * Ritorna la dimensione di una struttura passata come parametro.
 */
int get_struct_size(Type *type){
    int size = 0;

    for(Field *field = type->fields; field != NULL; field = field->next){
        size += get_domain_size(field->domain);
    }

    return size;
}

/**
 * Ritorna la dimensione di un tipo in formato stringa per la generazione di codice.
 */
int get_domain_size(Domain domain){
    switch(domain){
        case BOOLEAN_DOMAIN:
        case INTEGER_DOMAIN:
            return sizeof(int);

        case REAL_DOMAIN:
            return sizeof(float);

        case STRING_DOMAIN:
            return sizeof(char*);

        default:
            return 0;
    }
}

/**
 * Ritorna la dimensione della lista delle espressioni.
 */
int get_expr_list_size(Pnode node){
    int count = 0;

    while(node != NULL){
        count++;
        node = node->b;
    }

    return count;
}

/**
 * Calcola l'offset di un field rispetto all'origine.
 */
int calc_offset(Field *fields, Field *field){
    int count = 0;
    for(Field *f = fields; f->name != field->name; f = f->next)
        count += get_domain_size(f->domain);
    
    return count;
}

/**
 * Ritorna un Code di comparazione (EQUA, NEQU, BLNG, ...) dato il tipo e l'operazione.
 */
Code make_comp(Type *t1, Type *t2, SemanticValue op){
    if(op == VAL_EQ) 
        return makecode(EQUA);
    if(op == VAL_NE)
        return makecode(NEQU);
    if(op == VAL_IN)
        return makecode(BLNG);
    if(t1->domain == REAL_DOMAIN || t2->domain == REAL_DOMAIN)
        return make_real_comp(op);
    else if(t1->domain == INTEGER_DOMAIN)
        return make_int_comp(op);
    else
        return make_string_comp(op);
}

/**
 * Ritorna il Code di un'operazione di comparazione per numeri reali.
 */
Code make_real_comp(SemanticValue op){
    switch(op){
        case VAL_GT:
            return makecode(GTHR);
        case VAL_GE:
            return makecode(GEQR);
        case VAL_LT:
            return makecode(LTHR);
        case VAL_LE:
            return makecode(LEQR);
    }
}

/**
 * Ritorna il Code di un'operazione di comparazione per numeri interi.
 */
Code make_int_comp(SemanticValue op){
    switch(op){
        case VAL_GT:
            return makecode(GTHI);
        case VAL_GE:
            return makecode(GEQI);
        case VAL_LT:
            return makecode(LTHI);
        case VAL_LE:
            return makecode(LEQI);
    }
}

/**
 * Ritorna il Code di un'operazione di comparazione per stringhe.
 */
Code make_string_comp(SemanticValue op){
    switch(op){
        case VAL_GT:
            return makecode(GTHS);
        case VAL_GE:
            return makecode(GEQS);
        case VAL_LT:
            return makecode(LTHS);
        case VAL_LE:
            return makecode(LEQS);
    }
}

/**
 * Ritorna il Code di un'operazione matematica(ADD, SUB, MUL, DIV, ...).
 */
Code make_math(Type *t1, Type *t2, SemanticValue op){
    if(t1->domain == REAL_DOMAIN || t2->domain == REAL_DOMAIN)
        return make_real_math(op);
    else
        return make_int_math(op);
}

/**
 * Ritorna il Code di un'operazione matematica con numeri interi.
 */
Code make_int_math(SemanticValue op){
    switch(op){
        case VAL_PLUS:
            return makecode(ADDI);
        case VAL_MINUS:
            return makecode(SUBI);
        case VAL_TIMES:
            return makecode(MULI);
        case VAL_DIVIDE:
            return makecode(DIVI);
    }
}

/**
 * Ritorna il Code di un'operazione matematica con numeri reali.
 */
Code make_real_math(SemanticValue op){
    switch(op){
        case VAL_PLUS:
            return makecode(ADDR);
        case VAL_MINUS:
            return makecode(SUBR);
        case VAL_TIMES:
            return makecode(MULR);
        case VAL_DIVIDE:
            return makecode(DIVR);
    }
}

/**
 * Ritorna il Code di un'operazione di negazione.
 */
Code make_neg(Type *t){
    if(t->domain == REAL_DOMAIN)
        return makecode(NEGR);
    else if(t->domain == INTEGER_DOMAIN)
        return makecode(NEGI);
    else 
        return makecode(NEGB);
}

/**
 * Ritorna il Code di un'operazione di built in.
 */
Code make_built_in(SemanticValue op){
    switch(op){
        case VAL_REAL:
            return makecode(TORE);
        case VAL_INTEGER:
            return makecode(TOIN);
        case VAL_EMPTY:
            return makecode(EMPT);
        case VAL_HEAD:
            return makecode(HEAD);
        case VAL_TAIL:
            return makecode(TAIL);
        case VAL_CARD:
            return makecode(CARD);
    }
}