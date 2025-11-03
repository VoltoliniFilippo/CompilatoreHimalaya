#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen.h"

extern int lhs;
extern int param_counter;

// Funzioni ausiliarie
int calc_entry(Code code, int oid);
Code fix_func_call(Code code);
int count_vars();
SymbolTableEntry *get_vars();

// Funzioni di analisi del programma
Code semantic_analysis(Pnode root);
Code analyze_program(Pnode node);
void analyze_type_section(Pnode node);
void analyze_var_section(Pnode node);
Code analyze_func_section(Pnode node);
void analyze_type_decl(Pnode node);
void analyze_var_decl(Pnode node);
Code analyze_func_decl(Pnode node);
SymbolTableEntry *analyze_formal_decl_list(Pnode node);
SymbolTableEntry *analyze_formal_decl(Pnode node);
void analyze_id_list(Pnode node, Class cls, Type* type);
Code analyze_stat_list(Pnode node);
Code analyze_stat(Pnode node);
Code analyze_if_stat(Pnode node);
Code analyze_while_stat(Pnode node);
Code analyze_read_stat(Pnode node);
Code analyze_assign_stat(Pnode node);
Code analyze_for_stat(Pnode node);
Code analyze_write_stat(Pnode node);
Code analyze_expr(Pnode node);
Code analyze_struct_constructor(Pnode node);
Code analyze_expr_list(Pnode node);
Code analyze_vector_constructor(Pnode node);
Code analyze_built_in_expr(Pnode node);
Code analyze_range(Pnode node);
Code analyze_cond_expr(Pnode node);
Code analyze_func_call(Pnode node);
Code analyze_lhs(Pnode node);
Code analyze_indexing(Pnode node);
Code analyze_fielding(Pnode node);
Code analyze_opt_elsif_stat_list(Pnode node, int elseSize);
Code analyze_opt_else_stat(Pnode node);
Code analyze_logic_expr(Pnode node);
Code analyze_math_expr(Pnode node);
Code analyze_existing_id(Pnode node);
Code analyze_neg_expr(Pnode node);
Code analyze_comp_expr(Pnode node);
void analyze_new_id(Pnode node, Class cls, Type *type);
Code generate_vall_codes();
Code generate_vall_code(SymbolTableEntry *entry, Type *type);

// Funzioni che riguardano Type
Type* get_vector_type(Pnode node);
Type* analyze_type(Pnode node);
Type* get_expression_type(Pnode node);
Type* get_nonterminal_expression_type(Pnode node);
int types_compatible(Type* t1, Type* t2);
int is_numeric_domain(Type* type);
int is_boolean_domain(Type* type);
int count_expr_list_elements(Pnode node);
Domain *get_vector_child(Pnode node);
Field *get_fields_from_expr_list(Pnode node);
Field *find_field(Field *fields, char *id);
Field *get_fields(Pnode node);

// Funzioni di stampa
void print_generated_code(Code code);
void print_args(Operator op, Value args[3]);