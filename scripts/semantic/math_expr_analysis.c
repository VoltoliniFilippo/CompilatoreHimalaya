#include "semantic.h"

/**
 * Analizza un'espressione matematica, controlla se gli operandi sono numerici e analizza le espressioni matematiche.
 */
Code analyze_math_expr(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un'espressione matematica è risultato essere NULL", "");
        return endcode();
    }

    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo math-expr è NULL", "");
        return endcode();
    }

    if(node->c2 == NULL){
        print_error("Il figlio c2 del nodo math-expr è NULL", "");
        return endcode();
    }

    Code firstExpr;
    Code secondExpr;

    Type *t1 = get_expression_type(node->c1);
    Type *t2 = get_expression_type(node->c2);

    if(!(is_numeric_domain(t1) && is_numeric_domain(t2)) && node->value.ival != VAL_PLUSPLUS){
        print_error("Tipi incompatibili nell'operazione aritmetica", "");
        return endcode();
    }

    if((t1->domain != VECT_DOMAIN || t2->domain != VECT_DOMAIN) && node->value.ival == VAL_PLUSPLUS){
        print_error("I tipi per la concatenazione devono essere vettori", "");
        return endcode();
    }

    if((t1->domain == VECT_DOMAIN && t2->domain == VECT_DOMAIN) && node->value.ival == VAL_PLUSPLUS && *(t1->child) != *(t2->child)){
        print_error("I tipi dei vettori per la concatenazione devono essere identici", "");
        fprintf(stderr, "child1: %d child2: %d\n", *(t1->child), *(t2->child));
        return endcode();
    }

    Code mathCode;

    if(node->value.ival == VAL_PLUSPLUS){
        firstExpr = analyze_expr(node->c1);
        secondExpr = analyze_expr(node->c2);
        int fields1 = count_expr_list_elements(node->c1->c1);
        int fields2 = count_expr_list_elements(node->c2->c1);
        int fields = fields1 + fields2;
        int size = get_type_size(get_expression_type(node->c1->c1));
        
        if(size == -1)
            size = get_type_size(get_expression_type(node->c2->c1));

        if(size == -1)
            size = 0;

        mathCode = make_vect_grou(fields, size, -1);
    }
    else{
        firstExpr = analyze_expr(node->c1);
        secondExpr = analyze_expr(node->c2);
        mathCode = make_math(t1, t2, node->value.ival);
    }

    if(t1->domain == REAL_DOMAIN && t2->domain == INTEGER_DOMAIN)
        return concode(firstExpr, secondExpr, makecode(TORE), mathCode, endcode());
    else if(t1->domain == INTEGER_DOMAIN && t2->domain == REAL_DOMAIN)
        return concode(firstExpr, makecode(TORE), secondExpr, mathCode, endcode());
    else
        return concode(firstExpr, secondExpr, mathCode, endcode());
}

/**
 * Analizza un'espressione di negazione, controlla se l'operando è numerico (caso -) o booleano (caso not) e analizza l'espressione.
 */
Code analyze_neg_expr(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di un'espressione di negazione è risultato essere NULL", "");
        return endcode();
    }

    if(node->c1 == NULL){
        print_error("Il figlio c1 del nodo neg-expr è NULL", "");
        return endcode();
    }

    if(node->value.ival == VAL_MINUS){
        if(!is_numeric_domain(get_expression_type(node->c1))){
            print_error("Operando di negazione (-) deve essere numerico", "");
            return endcode();
        }
    }

    else if(node->value.ival == VAL_NOT){
        if(!is_boolean_domain(get_expression_type(node->c1))){
            print_error("Operando di negazione (NOT) deve essere boolean", "");
            return endcode();
        }
    }

    Code exprCode = analyze_expr(node->c1);
    
    Type *t = get_expression_type(node->c1);

    Code negCode = make_neg(t);

    return concode(exprCode, negCode, endcode());
}