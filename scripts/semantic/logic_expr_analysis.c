#include "semantic.h"

/**
 * Analizza un'espressione logica, controlla se gli operandi sono di tipo booleano e analizza le espressioni logiche.
 */
Code analyze_logic_expr(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un'espressione logica è risultato essere NULL", "");
        return endcode();
    }

    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo logic-expr è NULL", "");
        return endcode();
    }

    if(node->c2 == NULL){
        print_error("Il figlio c1 del nodo logic-expr è NULL", "");
        return endcode();
    }

    Code firstExpr = analyze_expr(node->c1);
    Code secondExpr = analyze_expr(node->c2);

    Type* left_type = get_expression_type(node->c1);
    Type* right_type = get_expression_type(node->c2);

    if(left_type->domain != BOOLEAN_DOMAIN || right_type->domain != BOOLEAN_DOMAIN){
        print_error("Entrambi gli operandi di un'espressione logica devono essere booleani", "");
        return endcode();
    }
    
    if(node->value.ival == VAL_AND)
        return concode(firstExpr, make_skip_offset(SKPF, secondExpr.size), secondExpr, makecode1(SKIP, 2), makecode1(LOCI, 0), endcode());
    else
        return concode(firstExpr, makecode1(SKPF, 3), makecode1(LOCI, 1), make_skip_exit(SKIP, secondExpr.size), secondExpr, endcode());
}

/**
 * Analizza un'espressione di confronto, controlla se gli operandi sono compatibili e analizza le espressioni di confronto.
 */
Code analyze_comp_expr(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un'espressione comparativa è risultato essere NULL", "");
        return endcode();
    }

    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo comp-expr è NULL", "");
        return endcode();
    }

    if(node->c2 == NULL){
        print_error("Il figlio c1 del nodo comp-expr è NULL", "");
        return endcode();
    }

    Code firstExpr = analyze_expr(node->c1);
    Code secondExpr = analyze_expr(node->c2);

    Type* left_type = get_expression_type(node->c1);
    Type* right_type = get_expression_type(node->c2);

    if(node->value.ival == VAL_IN){
        //Se il tipo del secondo elemento non è un vettore stampa un errore
        if(right_type->domain != VECT_DOMAIN){
            print_error("Il secondo operando di un'espressione di confronto con IN deve essere un vettore", "");
            return endcode();
        }

        //Se il tipo del vettore è NULL stampa un errore
        if(right_type->child == NULL){
            print_error("Il tipo del vettore è nullo","");
            return endcode();
        }

        //Se il tipo del primo elemento non è compatibile con il tipo del vettore stampa un errore.
        if(left_type->domain != *(right_type->child)){
            print_error("Il primo operando di un'espressione di confronto con IN deve essere dello stesso tipo degli elementi del vettore", "");
            return endcode();
        }
    }else{ //caso EQ, NE, LT, LE, GT,GE
        if(!types_compatible(left_type, right_type)){
            print_error("I tipi dell'espressione logica non sono compatibili", "");
            return endcode();
        }
    }

    Code compCode =  make_comp(left_type, right_type, node->value.ival);

    if(firstExpr.head == NULL)
        fprintf(stderr, "NULL 1\n");

    if(secondExpr.head == NULL)
        fprintf(stderr, "NULL 2\n");

    if(compCode.head == NULL)
        fprintf(stderr, "NULL 3\n");

    return concode(firstExpr, secondExpr, compCode, endcode());
}
