#include "semantic.h"

/**
 * Analizza un'espressione che contiene range, se il tipo delle espressioni non è intero stampa un errore.
 * Se expr1 > expr2 -> [epxr1 .. expr2] = []
 */
Code analyze_range(Pnode node){
    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo range è NULL", "");
        return endcode();
    }

    if(node->c2 == NULL){
        print_error("Il figlio c2 del nodo range è NULL", "");
        return endcode();
    }

    Code firstExpr = analyze_expr(node->c1);
    Code secondExpr = analyze_expr(node->c2);

    Type *t1 = get_expression_type(node->c1);
    Type *t2 = get_expression_type(node->c2);

    if(t1->domain != INTEGER_DOMAIN || t2->domain != INTEGER_DOMAIN){
        print_error("Una delle espressioni del range non è di tipo intero", "");
        return endcode();
    }

    return concode(firstExpr, secondExpr, makecode(RNGE), endcode());
}

/**
 * Analizza un'espressione condizionale.
 * Se l'espressione condizionale non è booleana o i tipi degli statement if e else sono diversi ritorna errore.
 */
Code analyze_cond_expr(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un'espressione condizionale è risultato essere NULL", "");
        return endcode();
    }
    
    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo cond-expr è NULL", "");
        return endcode();
    }

    if(node->c2 == NULL){
        print_error("Il figlio c2 del nodo cond-expr è NULL", "");
        return endcode();
    }

    if(node->c3 == NULL){
        print_error("Il figlio c3 del nodo cond-expr è NULL", "");
        return endcode();
    }

    if(!is_boolean_domain(get_expression_type(node->c1))){
        print_error("L'espressione condizionale non è booleana", "");
        return endcode();
    }

    Code firstExprCode = analyze_expr(node->c1);
    Code secondExprCode = analyze_expr(node->c2);
    Code thirdExprCode = analyze_expr(node->c3);

    Type *type1 = get_expression_type(node->c2);
    Type *type2 = get_expression_type(node->c3);

    if(type1->domain != type2->domain){
        print_error("I tipi delle espressioni if e else sono diversi", "");
        return endcode();
    }//da aggiungere il tipo della funzione

    return concode(firstExprCode, make_skip_offset(SKPF, secondExprCode.size), secondExprCode, make_skip_exit(SKIP, thirdExprCode.size), thirdExprCode, endcode());
}