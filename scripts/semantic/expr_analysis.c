#include <stdio.h>
#include "semantic.h"

/**
 * Analizza un'espressione, controlla se gli operandi sono di tipo booleano per le operazioni booleane e analizza i termini booleani.
 *  logic-expr | comp-expr | math-expr | neg-expr | built-in-expr 
 *  lhs | boolconst | intconst | realconst |strconst | 
 *  constructor | range | cond-expr | func-call
 */
Code analyze_expr(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi dell'expr è NULL", "");
        return endcode();
    }

    Code code;

    switch(node->symbol){
        case N_LOGIC_EXPR:
            code = analyze_logic_expr(node);
            break;

        case N_COMP_EXPR:
            code = analyze_comp_expr(node);
            break;

        case N_MATH_EXPR:
            code = analyze_math_expr(node);
            break; 

        case N_NEG_EXPR:
            code = analyze_neg_expr(node);
            break;

        case N_BUILT_IN_EXPR:
            code = analyze_built_in_expr(node);
            break;

        case N_LHS:
            code = analyze_lhs(node);
            break;

        case N_CONSTRUCTOR:
            if(node->value.ival == VAL_STRUCT)
                code = analyze_struct_constructor(node);
            else if(node->value.ival == VAL_VECT)
                code = analyze_vector_constructor(node);
            break;

        case N_RANGE:
            code = analyze_range(node);
            break;

        case N_COND_EXPR:
            code = analyze_cond_expr(node);
            break;

        case N_FUNC_CALL:
            code = analyze_func_call(node);
            break;

        case N_INDEXING:
            code = analyze_indexing(node->c1);
            break;

        case T_BOOLCONST:
        case T_INTCONST:
            code = make_loci(node->value.ival);
            break;

        case T_REALCONST:
            code = make_locr(node->value.rval);
            break;

        case T_STRCONST:
            code = make_locs(remove_quotes(node->value.sval));
            break; 

        default:
            print_error("Tipo di nodo non riconosciuto per l'espressione", "");
            code = endcode();
    }

    return code;
}

/**
 * Analizza una lista di espressioni.
 */
Code analyze_expr_list(Pnode node){
    if(node == NULL) return endcode();

    Code code = analyze_expr(node);
    node = node->b;

    while(node != NULL){
        code = concode(code, analyze_expr(node), endcode());
        node = node->b;
    }

    return code;
}