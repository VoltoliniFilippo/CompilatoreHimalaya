#include <stdio.h>
#include "semantic.h"

/**
 * Analizza la lista delle istruzioni, iterando su ogni nodo della lista e analizzando ciascuna istruzione.
 */
Code analyze_stat_list(Pnode node){
    if(node == NULL){
        print_error("La lista di statement è NULL", "");
        return endcode();
    }

    Code code = analyze_stat(node);
    node = node->b;

    while(node != NULL){
        code = concode(code, analyze_stat(node), endcode());
        node =  node->b;
    }

    return code;
}

/**
 * Analizza un'istruzione specifica in base al tipo di nodo.
 */
Code analyze_stat(Pnode node){
    Code code;
    switch(node->symbol){
        case N_READ_STAT:
            code = analyze_read_stat(node);
            break;
        
        case N_WRITE_STAT:
            code = analyze_write_stat(node);
            break;

        case N_ASSIGN_STAT: 
            code = analyze_assign_stat(node);
            break;

        case N_IF_STAT:
            code = analyze_if_stat(node);
            break;

        case N_WHILE_STAT:
            code = analyze_while_stat(node);
            break;

        case N_FOR_STAT:
            code = analyze_for_stat(node);
            break;

        default:
            code = endcode();
    }

    return code;
}

/**
 * Analizza un'istruzione while.
 */
Code analyze_while_stat(Pnode node){
    Code exprCode = analyze_expr(node->c1);
    Code statListCode = analyze_stat_list(node->c2);
    int size = exprCode.size + statListCode.size + 1;

    // il + 1 dopo statListCode.size dovuto allo skip successivo che bisogna saltare
    return concode(exprCode, make_skip_exit(SKPF, statListCode.size + 1), statListCode, make_skip_up(SKIP, size), endcode());
}

/**
 * Analizza un'istruzione if.
 */
Code analyze_if_stat(Pnode node){
    if(!is_boolean_domain(get_expression_type(node->c1))){
        print_error("L'espressione dell'if deve essere booleana", "");
        return endcode();
    }

    Code exprCode = analyze_expr(node->c1);
    Code statListCode = analyze_stat_list(node->c2);
    int next = statListCode.size;

    Code ifCode = concode(exprCode, make_skip_offset(SKPF, next), statListCode, endcode());
    Code elsifCode = endcode();
    Code elseCode = endcode();

    if(node->c4 != NULL)
        elseCode = analyze_opt_else_stat(node->c4);

    if(node->c3 != NULL)
        elsifCode = analyze_opt_elsif_stat_list(node->c3, elseCode.size);

    int size = elsifCode.size + elseCode.size;

    Code code;
    
    if(elsifCode.size > 0 && elseCode.size > 0)
        code = concode(ifCode, make_skip_exit(SKIP, size), elsifCode, elseCode, endcode());
    else
        code = concode(ifCode, make_skip_exit(SKIP, size), elseCode, endcode());

    return code;
}
/**
 * Analizza la dichiarazione opzionale di uno o più elsif.
 * Il nodo è opzionale quindi può essere NULL.
 */
Code analyze_opt_elsif_stat_list(Pnode node, int elseSize){
    int capacity = 4;
    Code *codes = malloc(capacity * sizeof(Code));
    int i = 0;

    while(node != NULL){
        if(i >= capacity){
            capacity *= 2;
            codes = realloc(codes, capacity * sizeof(Code));
        }

        Code exprCode = analyze_expr(node->c1);
        Code statListCode = analyze_stat_list(node->c2);

        if(node->c1 == NULL){
            print_error("Il figlio c1 del nodo opt-elsif-stat-list è NULL", "");
            return endcode();
        }

        if(node->c2 == NULL){
            print_error("Il figlio c2 del nodo opt-elsif-stat-list è NULL", "");
            return endcode();
        }

        Type* cond_type = get_expression_type(node->c1);
        
        if (cond_type != NULL && !is_boolean_domain(cond_type)) {
            print_error("La condizione dell'elsif deve essere di tipo boolean", "");
            return endcode();
        }

        int next = statListCode.size;
        Code code = concode(exprCode, make_skip_offset(SKPF, next), statListCode, endcode());
        codes[i] = code;
        node = node->b;
        ++i;
    }

    Code code = i > 0 ? codes[0] : endcode();

    for(int j = 0; j < i; j++){
        int size = elseSize;

        for(int k = j + 1; k < i; k++)
            size += codes[k].size + 1;

        code = concode(code, make_skip_exit(SKIP, size), endcode());
    }

    free(codes);
    return code;
}

/**
 * Analizza la dichiarazione opzionale di un else.
 * Il nodo è opzionale quindi può essere NULL.
 */
Code analyze_opt_else_stat(Pnode node){
    return analyze_stat(node);
}

/**
 * Analizza un'istruzione di lettura, controlla se l'identificatore è stato dichiarato e se è un parametro.
 */
Code analyze_read_stat(Pnode node){
    //Nome dell'id da leggere
    char *id = node->c1->value.sval;

    SymbolTableEntry *entry = lookup_symbol(id);

    //Se l'identificatore non è stato dichiarato stampa un errore
    if(entry == NULL) {
        print_error("Errore: identificatore non dichiarato", id);
        return endcode();
    }

    //Se l'identificatore è un parametro stampa un errore
    if(entry->class == PARAM_CLASS){
        print_error("Errore: non si può leggere un valore da assegnare ad un parametro", id);
        return endcode();
    }//Controllare

    return make_read(entry->oid, get_format(entry->type));
}

/**
 * Analizza un'istruzione di assegnamento, controlla se il tipo dell'espressione è compatibile con il tipo della variabile.
 */
Code analyze_assign_stat(Pnode node){
    lhs = 1;
    Code lhsCode = analyze_lhs(node->c1);
    lhs = 0;
    Code exprCode = analyze_expr(node->c2);

    Type* lhs_type = get_expression_type(node->c1);
    Type* rhs_type = get_expression_type(node->c2);

    if(!types_compatible(lhs_type, rhs_type)){
        print_error("Tipi incompatibili nell'assegnamento", "");
        return endcode();
    }

    if(lhs_type->domain == REAL_DOMAIN && rhs_type->domain == INTEGER_DOMAIN)
        return concode(lhsCode, exprCode, makecode(TORE), makecode(STOR), endcode());
    else
        return concode(lhsCode, exprCode, makecode(STOR), endcode());
}

/**
 * Analizza un'istruzione di ciclo for, controlla se l'identificatore è stato dichiarato e se gli estremi del ciclo sono numerici.
 */
Code analyze_for_stat(Pnode node){
    char *id = node->c1->value.sval;

    SymbolTableEntry *idEntry = lookup_symbol(id);

    if(idEntry == NULL){
        Type *int_type = create_type(INTEGER_DOMAIN);
        idEntry = insert_symbol(id, VAR_CLASS, int_type);
    }

    Code firstExpr = analyze_expr(node->c2);
    Code secondExpr = analyze_expr(node->c3);
    Code statList = analyze_stat_list(node->c4);

    Type* start_type = get_expression_type(node->c2);
    Type* end_type = get_expression_type(node->c3);

    if(start_type->domain != INTEGER_DOMAIN){
        print_error("L'estremo iniziale del for deve essere intero", "");
        return endcode();
    }

    if(end_type->domain != INTEGER_DOMAIN){
        print_error("L'estremo finale del for deve essere intero", "");
        return endcode();
    }

    char temp_name[32];
    int temp_counter = 0;
    SymbolTableEntry *tempEntry = NULL;

    do {
        snprintf(temp_name, sizeof(temp_name), "temp_%d", temp_counter++);
        tempEntry = lookup_symbol(temp_name);
    } while(tempEntry != NULL);

    tempEntry = insert_symbol(temp_name, VAR_CLASS, create_type(INTEGER_DOMAIN)); //da inserire in una funzione

    Code storeId = concode(make_loda(0, idEntry->oid), firstExpr, makecode(STOR), endcode());
    Code storeTemp = concode(make_loda(0, tempEntry->oid), secondExpr, makecode(STOR), endcode());
    Code lessEqual = concode(make_load(0, idEntry->oid), make_load(0, tempEntry->oid), makecode(LEQI), endcode());
    Code addOne = concode(make_loda(0, idEntry->oid), make_load(0, idEntry->oid), make_loci(1), makecode(ADDI), makecode(STOR), endcode());
    int skipUpSize = lessEqual.size + statList.size + addOne.size + 1; //+1 dovuto allo skip inserito sotto, stessa cosa nello SKPF

    return concode(storeId, storeTemp, lessEqual, make_skip_exit(SKPF, addOne.size + statList.size + 1), statList, addOne, make_skip_up(SKIP, skipUpSize), endcode());
}

/**
 * Analizza un'istruzione di scrittura.
 */
Code analyze_write_stat(Pnode node){  
    Operator op = node->value.ival == VAL_WRITE ? WRTE : WRTL;

    char *s_type = get_format(get_expression_type(node->c1));

    Code exprCode = analyze_expr(node->c1);
    Code strCode = makecode_str(op, s_type);

    return concode(exprCode, strCode, endcode());
}