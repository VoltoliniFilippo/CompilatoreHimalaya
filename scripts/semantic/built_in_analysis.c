#include "semantic.h"

/**
 * Analizza un'espressione built-in, controlla se il tipo dell'espressione è compatibile con il tipo atteso e analizza l'espressione.
 * INTEGER | REAL -> si aspetta un tipo numerico (int o real)
 * EMPTY | HEAD | TAIL -> si aspetta un vettore
 */
Code analyze_built_in_expr(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un'espressione di built in è risultato essere NULL", "");
        return endcode();
    }

    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo built-in-expr è NULL", "");
        return endcode();
    }

    if(node->value.ival == VAL_INTEGER || node->value.ival == VAL_REAL){
        if(!is_numeric_domain(get_expression_type(node->c1))){
            print_error("Operando di built-in deve essere intero o reale", "");
            return endcode();
        }
    }else{
        if(get_expression_type(node->c1)->domain != VECT_DOMAIN){
            print_error("Operando di built-in deve essere un vettore", "");
            return endcode();
        }
    }

    Code exprCode = analyze_expr(node->c1);
    Code builtInCode = make_built_in(node->value.ival);

    return concode(exprCode, builtInCode, endcode());
}
