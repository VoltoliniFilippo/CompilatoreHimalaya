#include <stdio.h>
#include "semantic.h"

/**
 * Analizza il tipo di un espressione.
 */
Type* analyze_type(Pnode node){
    if(node == NULL){
        print_error("Nell'analisi del tipo un nodo è risultato essere NULL", "");
        return NULL;
    }

    switch(node->symbol){
        case T_BOOLEAN:
            return create_type(BOOLEAN_DOMAIN);
        
        case T_INTEGER:
            return create_type(INTEGER_DOMAIN);

        case T_REAL:
            return create_type(REAL_DOMAIN);

        case T_STRING:
            return create_type(STRING_DOMAIN);

        case T_ID:
            SymbolTableEntry *entry = lookup_symbol(node->value.sval);
            return entry->type;

        case N_STRUCT_TYPE:
            return create_struct_type(get_fields(node->c1));//mancano i fields

        case N_VECTOR_TYPE:
            Domain *child = get_vector_child(node->c1);
            Field *fields = NULL;

            if(*child == STRUCT_DOMAIN)
                fields = get_fields(node->c1->c1);
            
            return create_vector_type(child, fields);

        default:
            return NULL;
    }
}

Domain *get_vector_child(Pnode node){
    if(node == NULL){
        print_error("Nell'analisi del tipo un nodo è risultato essere NULL", "");
        return NULL;
    }

    Domain *child = (Domain*)malloc(sizeof(Domain));

    switch(node->symbol){
        case T_BOOLEAN:
            *child = BOOLEAN_DOMAIN;
            break;
        
        case T_INTEGER:
            *child = INTEGER_DOMAIN;
            break;

        case T_REAL:
            *child = REAL_DOMAIN;
            break;

        case T_STRING:
            *child = STRING_DOMAIN;
            break;

        case T_ID:
            SymbolTableEntry *entry = lookup_symbol(node->value.sval);
            if(entry->class == TYPE_CLASS){
                *child = entry->type->domain;
                break;
            }

            print_error("Tipo non definito: ", node->value.sval);
            free(child);
            return NULL;

        case N_STRUCT_TYPE:
            *child = STRUCT_DOMAIN;
            break;
        
        default:
            *child = EMPTY_DOMAIN;
    }

    return child;
}

/**
 * Ritorna i campi di una struttura.
 */
Field *get_fields(Pnode node){
    if(node == NULL)
        return NULL;
    
    Field *field = (Field*)malloc(sizeof(Field));
    field->name = strdup(node->c1->value.sval);
    field->domain = analyze_type(node->c2)->domain;
    field->next = get_fields(node->b);

    return field;
}

/**
 * Ritorna il Field associato all'id inserito a partire dai fields della struct.
 * Ritorna NULL se non si trovano corrispondenze.
 */
Field *find_field(Field *fields, char *id){
    for(Field *f = fields; f != NULL; f = f->next){
        if(strcmp(f->name, id) == 0)
            return f;
    }

    return NULL;
}

/**
 * Ritorna un nuovo tipo vettore creato a partire da child e fields.
 */
Type* get_vector_type(Pnode node){
    Type *type = get_expression_type(node->c1);

    //Type *fields = get_fields(node->c1); FIELDS DISATTIVATI AL MOMENTO
            
    Domain child = EMPTY_DOMAIN;

    if(type != NULL)
        child = type->domain;

    return create_vector_type(&child, NULL);
}

/**
 * Ritorna il tipo dell'espressione
 */
Type* get_expression_type(Pnode node){
    if(node == NULL)
        return NULL;

    switch(node->symbol){
        case T_BOOLEAN:
        case T_BOOLCONST:
            return create_type(BOOLEAN_DOMAIN);
        
        case T_INTEGER:
        case T_INTCONST:
            return create_type(INTEGER_DOMAIN);

        case T_REAL:
        case T_REALCONST:
            return create_type(REAL_DOMAIN);

        case T_STRING:
        case T_STRCONST:
            return create_type(STRING_DOMAIN);

        case T_ID:
            SymbolTableEntry *entry = lookup_local(node->value.sval);
            if(entry == NULL)
                entry = lookup_symbol(node->value.sval);

            if(entry == NULL) {
                print_error("Identificatore non definito: ", node->value.sval);
                return NULL;
            }
            return entry->type;

        default:
            return get_nonterminal_expression_type(node);
    }
}

/**
 * Ritorna il tipo di un'espressione nonterminale.
 */
Type* get_nonterminal_expression_type(Pnode node){
    switch (node->symbol)
    {
        case N_VECTOR_TYPE:
            return get_vector_type(node);

        case N_STRUCT_TYPE:
            return create_struct_type(get_fields(node->c1));

        case N_LOGIC_EXPR:
            return create_type(BOOLEAN_DOMAIN);

        case N_COMP_EXPR:
            return create_type(BOOLEAN_DOMAIN);

        case N_MATH_EXPR:
            if(node->value.ival == VAL_PLUSPLUS)
                return get_expression_type(node->c1);
            else if(get_expression_type(node->c1)->domain == REAL_DOMAIN || get_expression_type(node->c2)->domain == REAL_DOMAIN)
                return create_type(REAL_DOMAIN);
            return create_type(INTEGER_DOMAIN);

        case N_NEG_EXPR:
            if(node->value.ival == VAL_MINUS && is_numeric_domain(get_expression_type(node->c1)))
                return get_expression_type(node->c1);
            else if(node->value.ival == VAL_NOT && is_boolean_domain(get_expression_type(node->c1)))
                return create_type(BOOLEAN_DOMAIN);
            else
                return NULL;
            
        case N_BUILT_IN_EXPR:
            if(node->value.ival == VAL_INTEGER)
                return create_type(INTEGER_DOMAIN);
            else if(node->value.ival == VAL_REAL)
                return create_type(REAL_DOMAIN);
            else if(node->value.ival == VAL_CARD)
                return create_type(INTEGER_DOMAIN);
            else if(node->value.ival == VAL_EMPTY && get_expression_type(node->c1)->domain == VECT_DOMAIN)
                return create_type(BOOLEAN_DOMAIN);
            else if(get_expression_type(node->c1)->domain == VECT_DOMAIN) //VAL_HEAD e VAL_TAIL
                return get_expression_type(node->c1);
            else
                return NULL;

        case N_LHS:
            if(node->c1->symbol == N_INDEXING){
                return get_expression_type(node->c1);
            }
            else if(node->c2 == NULL){
                return get_expression_type(node->c1);
            }else{
                char *id1 = node->c1->value.sval;
                char *id2 = node->c2->value.sval;
                SymbolTableEntry *entry = lookup_symbol(id1);
                Field *fields = entry->type->fields;
                Field *field = find_field(fields, id2);
                return create_type(field->domain);
            }

        case N_INDEXING:
            return analyze_type(node->c1);
        
        case N_CONSTRUCTOR:
            if(node->value.ival == VAL_STRUCT){
                Field *fields = get_fields_from_expr_list(node->c1);
                return create_struct_type(fields);
            }
            else if(node->value.ival == VAL_VECT){
                return get_vector_type(node);
            }
            
        case N_RANGE:
            Domain domain = INTEGER_DOMAIN;
            return create_vector_type(&domain, NULL);

        
        case N_COND_EXPR:
            return get_expression_type(node->c2);

        case N_FUNC_CALL:
            char* func_name = node->value.sval;
            SymbolTableEntry* func_entry = lookup_symbol(func_name);
            return func_entry->type;

        default:
            print_error("Tipo di nodo non riconosciuto per l'espressione", "");
            return NULL;
    }
}

Field *get_fields_from_expr_list(Pnode node){
    if(node == NULL){
        print_error("Il nodo fornito per i campi dalla lista di espressioni è NULL", "");
        return NULL;
    }

    Field *fields = NULL;
    Field *current_field = NULL;
    analyze_expr(node);

    Type *type = get_expression_type(node);
    fields = malloc(sizeof(Field));
    fields->domain = type->domain;
    fields->next = NULL;
    current_field = fields;
    node = node->b;

    while(node != NULL) {
        analyze_expr(node);
        Type *field_type = get_expression_type(node);
        
        Field *new_field = malloc(sizeof(Field));
        new_field->domain = field_type->domain;
        new_field->next = NULL;
    
        current_field->next = new_field;
        current_field = new_field;
        
        node = node->b;
    }

    return fields;
}

/**
 * Ritorna 1 se i due tipi sono compatibili, altrimenti 0.
 */
int types_compatible(Type* t1, Type* t2){
    if(t1 == NULL || t2 == NULL) return 0;
    if(t1->domain == t2->domain) return 1;
    //if(t1->domain == t2->domain && t1->domain == VECT_DOMAIN && (Domain)t1->child == (Domain)t2->child) return 1;

    //Integer e real sono compatibili per assegnamento
    if(t1->domain == REAL_DOMAIN && t2->domain == INTEGER_DOMAIN) return 1;
    if(t1->domain == INTEGER_DOMAIN && t2->domain == REAL_DOMAIN) return 1;

    return 0;
}

/**
 * Ritorna 1 se il tipo è di dominio INTEGER o REAL, altrimenti 0.
 */
int is_numeric_domain(Type* type){
    if(type == NULL) return 0;
    return (type->domain == INTEGER_DOMAIN || type->domain == REAL_DOMAIN);
}

/**
 * Ritorna 1 se il tipo è di dominio BOOLEAN, altrimenti 0.
 */
int is_boolean_domain(Type* type){
    if(type == NULL) return 0;
    return (type->domain == BOOLEAN_DOMAIN);
}

/**
 * Conta il numero di nodi fratelli di una lista di expr.
 */
int count_expr_list_elements(Pnode node){
    if(node == NULL) return 0;
    
    int count = 1;
    Pnode current = node->b;
    
    while(current != NULL) {
        count++;
        current = current->b;
    }
    
    return count;
}