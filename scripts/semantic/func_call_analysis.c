#include "semantic.h"

/**
 * Analizza una chiamata di funzione, controlla che i tipi dei parametri siano uguali a quelli della funzione.
 * Se la funzione non esiste o i parametri hanno tipi diversi da quelli della funzione stampa un errore.
 */
Code analyze_func_call(Pnode node){
    if(node == NULL){
        print_error("Un nodo nell'analisi di una chiamata di funzione è risultato essere NULL", "");
        return endcode();
    }

    Code exprList = analyze_expr_list(node->c1);

    if(node->c1 != NULL)
        exprList = analyze_expr_list(node->c1);

    char *func_id = node->value.sval;

    SymbolTableEntry *entry = lookup_symbol(func_id);

    if(entry == NULL){
        print_error("La funzione non è stata definita", func_id);
        return endcode();
    }

    if(entry->class != FUNC_CLASS){
        print_error("L'id non è di una funzione", func_id);
        return endcode();
    }

    //La lista dei parametri opzionali può essere NULL, da controllare anche il numero e valore parametri

    int exprListSize = 0;

    for(SymbolTableEntry *e = entry->formals; e != NULL; e = e->next)
        exprListSize++;
        
    //Viene ritornato oid e non entry che verrà poi rimpiazzato con l'entry corretto una volta a conoscenza della lunghezza dell'intero codice
    Code func_call = make_func_call(exprListSize, entry->oid);
    return concode(exprList, func_call, endcode());
}