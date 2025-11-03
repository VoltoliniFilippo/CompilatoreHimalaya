#include "semantic.h"

/**
 * Analizza il costruttore per una struttura.
 */
Code analyze_struct_constructor(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un costruttore di struttura è risultato essere NULL", "");
        return endcode();
    }

    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo struct-constructor è NULL", "");
        return endcode();
    }
    
    Code exprListCode = analyze_expr_list(node->c1);
    Type *t = get_expression_type(node);
    int structSize = get_struct_size(t);
    return concode(exprListCode, make_struct_grou(get_expr_list_size(node->c1), structSize), endcode());
}

/**
 * Analizza il costruttore di un vettore.
 */
Code analyze_vector_constructor(Pnode node){
    //La lista di espressioni è opzionale quindi può essere NULL
    if(node->c1 == NULL)
        return make_vect_grou(0,0,0);
    else{
        Code exprListCode = analyze_expr_list(node->c1);
        int numberOfElements = count_expr_list_elements(node->c1);
        int vectSize = get_type_size(get_expression_type(node->c1));
        Code grou = make_vect_grou(numberOfElements, vectSize, numberOfElements);
        
        return concode(exprListCode, grou, endcode());
    }
}
