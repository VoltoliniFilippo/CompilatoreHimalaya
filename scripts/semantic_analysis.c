#include <stdio.h>
#include "semantic.h"

int lhs = 0;

/**
 * Funzione iniziale per l'analisi semantica stampa una stringa di inizio ed analizza il programma a partire dal nodo radice.
 */
Code semantic_analysis(Pnode root)
{
    if(root == NULL){
        print_error("Il nodo radice è NULL", "");
        return endcode();
    }

    Code gencode = analyze_program(root);
    return gencode;
}

/**
 * Ritorna il numero di istruzione in cui viene definita una funzione.
 */
int calc_entry(Code code, int oid){
    int i = 0;
    
    for(Stat *stat = code.head; stat != NULL; stat = stat->next){
        if(stat->op == FUNC && stat->args[0].ival == oid)
            return i;
        ++i;
    } 
}

/**
 * Aggiorna il numero della entry del codice JUMP della func call con l'entry esatto.
 * Fatto a posteriori in modo tale da avere tutto il codice completo.
 */
Code fix_func_call(Code code){
    for(Stat *stat = code.head; stat != NULL; stat = stat->next){
        if(stat->op == JUMP){
            int oid = stat->args[0].ival;
            int entry = calc_entry(code, oid);
            stat->args[0].ival = entry;
        }
    } 

    return code;
}

/**
 * Analizza il programma a partire dal nodo program, stampa una stringa di inizio, analizza le varie sezioni e stampa una stringa finale.
 */
Code analyze_program(Pnode node){
    Code haltCode = makecode(HALT);
    analyze_type_section(node->c1);
    analyze_var_section(node->c2);
    Code funcSection = analyze_func_section(node->c3);
    Code statList = analyze_stat_list(node->c4);
    Code varsCode = make_vars(count_vars());
    Code code;
    Code vallCode = generate_vall_codes();

    if(vallCode.size > 0)
        code = concode(varsCode, vallCode, statList, haltCode, funcSection, endcode());
    else
        code = concode(varsCode, statList, haltCode, funcSection, endcode());

    Code hCode = make_hcod(code_size(code));
    code = concode(hCode, code, endcode());
    code = fix_func_call(code);
    return code;
}

/**
 * Analizza ogni dichiarazione contenuta nella lista.
 * Il nodo può essere NULL, in tal caso non fa nulla.
 */
void analyze_type_section(Pnode node){
    if(node == NULL) return;

    analyze_type_decl(node);
    node = node->b;

    while(node != NULL){
        analyze_type_decl(node);
        node = node->b;
    }
}

/**
 * Analizza una dichiarazione di tipo e lo inserisce nella symbol table.
 */
void analyze_type_decl(Pnode node){
    Type *type = analyze_type(node->c2);

    analyze_id_list(node->c1, TYPE_CLASS, type);
}

/**
 * Analizza ogni dichiarazione contenuta nella lista.
 * Il nodo può essere NULL, in tal caso non fa nulla.
 */
void analyze_var_section(Pnode node){
    if(node == NULL) return;

    analyze_var_decl(node);
    node = node->b;

    while(node != NULL){
        analyze_var_decl(node);
        node = node->b;
    }
}

/**
 * Analizza una dichiarazione di variabile e la inserisce nella symbol table.
 */
void analyze_var_decl(Pnode node){
    if(node == NULL){
        print_error("Un nodo riguardante la dichiarazione di variabil è NULL", "");
        return;
    }

    Type *type = analyze_type(node->c2);

    analyze_id_list(node->c1, VAR_CLASS, type);
}

/**
 * Analizza ogni dichiarazione di funzione contenuta nella lista.
 * Il nodo può essere NULL, in tal caso non fa nulla.
 */
Code analyze_func_section(Pnode node){    
    if(node == NULL) 
        return endcode();

    Code code = analyze_func_decl(node);
    node = node->b;

    while(node != NULL){
        Code nextCode = analyze_func_decl(node);  
        code = concode(code, nextCode, endcode());

        node = node->b;
    }

    return code;
}

/**
 * Analizza una dichiarazione di funzione e la inserisce nella symbol table.
 * Stampa un errore se il nome della funzione esiste già nella symbol table oppure perché il tipo dell'espressione e il tipo di ritorno sono diversi.
 */
Code analyze_func_decl(Pnode node){
    if(node == NULL){
        print_error("Un nodo riguardante la dichiarazione di funzioni è NULL", "");
        return endcode();
    }

    //Nome della funzione
    char* func_name = node->value.sval;

    //Tipo di ritorno
    Type* return_type = analyze_type(node->c2);

    //Se il tipo di ritorno è NULL, stampa un errore
    if(return_type == NULL){
        print_error("Tipo di ritorno non valido per la funzione ", func_name);
        return endcode();
    }

    // Entra in un nuovo scope per i parametri
    enter_scope();

    // Reset del contatore dei parametri
    param_counter = 0;

    // Analizza i parametri formali e li assegna alla funzione
    analyze_formal_decl_list(node->c1);


    //Inserisci la funzione nella symbol table
    SymbolTableEntry *func_entry = insert_symbol(func_name, FUNC_CLASS, return_type);

    // Se la funzione è già stata inserita nella symbol table stampa un errore
    if(func_entry == NULL) {
        print_error("Errore: la funzione '%s' è già definita.\n", func_name);
        return endcode();
    }

    Code funcCode = make_func(func_entry->oid);
    Code exprCode = analyze_expr(node->c3);

    //Analizza il corpo della funzione
    Type* expr_type = get_expression_type(node->c2);

    if(expr_type == NULL){
        print_error("Il tipo dell'espressione della dichiarazione della funzione è NULL", func_name);
        return endcode();
    }

    //Se il tipo dell'espressione di ritorno non è compatibile con il tipo dichiarato per la funzione, stampa un errore
    if(!types_compatible(return_type, expr_type)){
        print_error("Tipo dell'espressione di ritorno non compatibile con il tipo dichiarato per la funzione ", func_name);
        return endcode();
    }

    // Esce dallo scope
    exit_scope();

    return concode(funcCode, exprCode, makecode(RETN), endcode());
}

/**
 * Analizza una lista di dichiarazioni di parametri formali.
 * Il nodo può essere NULL, in tal caso non fa nulla.
 */
SymbolTableEntry *analyze_formal_decl_list(Pnode node){
    if(node == NULL) 
        return NULL;
        
    SymbolTableEntry *head = analyze_formal_decl(node);
    SymbolTableEntry *current = head;
    node = node->b;

    while(node != NULL){
        current->next = analyze_formal_decl(node);
        node = node->b;
    }

    return head;
}

/**
 * Analiza una dichiarazione di parametro formale e lo inserisce nella symbol table.
 * Stampa un errore se il parametro è già definito.
 */
SymbolTableEntry *analyze_formal_decl(Pnode node){
    if(node == NULL){
        print_error("Un nodo riguardante la dichiarazione di parametri formali è NULL", "");
        return NULL;
    }

    //Nome del parametro
    char* param_name = node->value.sval;

    //Tipo del parametro
    Type *param_type = analyze_type(node->c1);    

    //Inserisci il parametro nella symbol table
    SymbolTableEntry *param_entry = insert_symbol(param_name, PARAM_CLASS, param_type);
    //if(param_entry != NULL)
      //  printf("PARAM NAME: %s\n", param_entry->name);
    

    //Se il parametro è già stato inserito nella symbol table stampa un errore
    if (param_entry == NULL) {
        print_error("Errore nell'inserimento del parametro", param_name);
        return NULL;
    }

    return param_entry;
}

/**
 * Analizza una lista di identificatori e li inserisce nella symbol table;
 * Stampa un errore se un identificatore è già definito.
 */
void analyze_id_list(Pnode node, Class cls, Type *type){
    if(node == NULL){
        print_error("Un nodo riguardante l'id-list è NULL", "");
        return;
    }
    
    analyze_new_id(node, cls, type);
    node = node->b;

    while(node != NULL){
        analyze_new_id(node, cls, type);
        node = node->b;
    }
}

/**
 * Analizza un nuovo id e lo inserisce nella symbol table.
 */
void analyze_new_id(Pnode node, Class cls, Type *type){
    if(node == NULL){
        print_error("Un nodo riguardante l'analisi di un nuovo id è NULL", "");
        return;
    }

    //Nome dell'id
    char* id = node->value.sval;

    //Inserisci l'id nella symbol table
    SymbolTableEntry *entry = insert_symbol(id, cls, type);

    //Se l'identificatore è già definito stampa un errore
    if(entry == NULL) {
        print_error("Errore: l'identificatore '%s' è già definito.\n", id);
        return;
    }
}

/**
 * Genera i codici vall per la definizione di variabili.
 */
Code generate_vall_codes(){
    SymbolTableEntry *vars = get_vars();
    int size = count_vars();
    Code code = endcode();

    for(int i = 0; i < size; i++){
        if(code.size == 0)
            code = generate_vall_code(&vars[i], vars[i].type);
        else
            code = concode(code, generate_vall_code(&vars[i], vars[i].type), endcode());
    }

    return code;
}

/**
 * Genera il codice per l'istruzione vall di un entry date l'entry della symbol table e il tipo.
 */
Code generate_vall_code(SymbolTableEntry *entry, Type *type){
    return make_vall(get_type_size(type), get_num_of_elements(entry));
}