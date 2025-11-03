#include "semantic.h"

/**
 * Analizza un'espressione lhs dividendo tra indexing e id opt-fielding.
 */
Code analyze_lhs(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un'espressione lhs è risultato essere NULL", "");
        return endcode();
    }

    if(node->c1->symbol == N_INDEXING){
        return analyze_indexing(node->c1);
    }else{
        if(node->c1 == NULL){
            print_error("Il figlio c1 del nodo lhs è NULL", "");
            return endcode();
        }
         
        if(node->c2 != NULL){
            return analyze_fielding(node);
        }else{
            return analyze_existing_id(node->c1);
        }
    }
}

/**
 * Analizza un'espressione di fielding
 */
Code analyze_fielding(Pnode node){
    char *id1 = node->c1->value.sval;
    char *id2 = node->c2->value.sval;

    SymbolTableEntry *entry = lookup_symbol(id1);
    
    if(entry->type->domain != STRUCT_DOMAIN){
        print_error("L'id non è una struttura", id1);
        return endcode();
    }

    Code idCode = analyze_existing_id(node->c1);

    Field *fields = entry->type->fields;
    Field *field = find_field(fields, id2);
    int offset = calc_offset(fields, field);

    if(field == NULL){
        print_error("Non è stato trovato il campo", id2);
        return endcode();
    }

    Code fielding = make_inld(offset, get_domain_size(field->domain));

    return concode(idCode, fielding, endcode());
}

/**
 * Analizza un'espressione di indexing.
 */
Code analyze_indexing(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un'espressione di indexing è risultato essere NULL", "");
        return endcode();
    }
    
    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo indexing è NULL", "");
        return endcode();
    }

    if(node->c2 == NULL){
        print_error("Il figlio c2 del nodo indexing è NULL", "");
        return endcode();
    }

    Code firstExpr = analyze_existing_id(node->c1);
    Code secondExpr = analyze_expr(node->c2);

    if(node->c3 != NULL)
        return concode(firstExpr, secondExpr, analyze_expr(node->c3), make_indexing(0,0, sizeof(int)), endcode()); // DA SISTEMARE
    
    return concode(firstExpr, secondExpr, make_indexing(sizeof(int), 0, sizeof(int)), endcode());
}

/**
 * Analizza un id già esistente, se non si trova nella symbol table si stampa un errore.
 */
Code analyze_existing_id(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un id esistente è risultato essere NULL", "");
        return endcode();
    }

    //Nome dell'id
    char *id = node->value.sval;

    SymbolTableEntry *entry = lookup_local(id);
    
    if(entry == NULL)
        entry = lookup_symbol(id);

    if(entry == NULL){ 
        print_error("L'id non esiste", "");
        return endcode();
    }

    int env = entry->class == VAR_CLASS ? 0 : 1;

    if(lhs)
        return make_loda(env, entry->oid);
    else
        return make_load(env, entry->oid);
}