# Directories
OUT_DIR := output
SRC_DIR := scripts
INSTR_DIR := scripts/instructions
SEMANTIC_DIR := scripts/semantic

# Compiler and flags
CC := cc
CFLAGS := -g -I$(SRC_DIR) -I$(OUT_DIR)

# Object files
OBJS := $(OUT_DIR)/lexer.o $(OUT_DIR)/parser.o $(OUT_DIR)/tree.o \
        $(OUT_DIR)/semantic_analysis.o $(OUT_DIR)/expr_analysis.o \
        $(OUT_DIR)/stat_analysis.o $(OUT_DIR)/types.o \
		$(OUT_DIR)/built_in_analysis.o $(OUT_DIR)/constructor_analysis.o \
		$(OUT_DIR)/control_expr_analysis.o $(OUT_DIR)/func_call_analysis.o \
		$(OUT_DIR)/lhs_analysis.o $(OUT_DIR)/logic_expr_analysis.o \
		$(OUT_DIR)/math_expr_analysis.o \
        $(OUT_DIR)/gen_func.o $(OUT_DIR)/gen.o \
        $(OUT_DIR)/print_code.o $(OUT_DIR)/virtual_machine.o \
        $(OUT_DIR)/arithmetic.o $(OUT_DIR)/built_in.o \
        $(OUT_DIR)/comparison.o $(OUT_DIR)/flow.o $(OUT_DIR)/io.o \
        $(OUT_DIR)/logical.o $(OUT_DIR)/vars.o $(OUT_DIR)/symtab.o

# Main target
compiler: $(OBJS)
	cc -g -o $@ $^

# Create output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

#Lexer.c
$(OUT_DIR)/lexer.c: $(SRC_DIR)/lexer.lex $(OUT_DIR)/parser.h | $(OUT_DIR)
	flex -o $(OUT_DIR)/lexer.c $(SRC_DIR)/lexer.lex

#Parser.h
$(OUT_DIR)/parser.h $(OUT_DIR)/parser.c: $(SRC_DIR)/parser.y | $(OUT_DIR)
	bison -dv -o $(OUT_DIR)/parser.c $(SRC_DIR)/parser.y

#Lexer.o
$(OUT_DIR)/lexer.o: $(OUT_DIR)/lexer.c $(OUT_DIR)/parser.h $(SRC_DIR)/def.h
	cc -g -c $(OUT_DIR)/lexer.c -o $(OUT_DIR)/lexer.o -I$(SRC_DIR) -I$(OUT_DIR)

#Parser.h
$(OUT_DIR)/parser.o: $(OUT_DIR)/parser.c $(SRC_DIR)/semantic.h $(SRC_DIR)/def.h $(SRC_DIR)/gen.h
	cc -g -c $(OUT_DIR)/parser.c -o $(OUT_DIR)/parser.o -I$(SRC_DIR) -I$(OUT_DIR)

#Tree.o
$(OUT_DIR)/tree.o: $(SRC_DIR)/tree.c $(SRC_DIR)/def.h
	cc -g -c $(SRC_DIR)/tree.c -o $(OUT_DIR)/tree.o -I$(SRC_DIR)

#Symtab.o
$(OUT_DIR)/symtab.o: $(SRC_DIR)/symtab.c $(SRC_DIR)/def.h
	cc -g -c $(SRC_DIR)/symtab.c -o $(OUT_DIR)/symtab.o -I$(SRC_DIR)

#Semantic_analysis.o
$(OUT_DIR)/semantic_analysis.o: $(SRC_DIR)/semantic_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SRC_DIR)/semantic_analysis.c -o $(OUT_DIR)/semantic_analysis.o -I$(SRC_DIR)

#Regole per gli script che contengono analisi semantica (da semantic/)
$(OUT_DIR)/expr_analysis.o: $(SEMANTIC_DIR)/expr_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/expr_analysis.c -o $(OUT_DIR)/expr_analysis.o -I$(SRC_DIR)

$(OUT_DIR)/stat_analysis.o: $(SEMANTIC_DIR)/stat_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/stat_analysis.c -o $(OUT_DIR)/stat_analysis.o -I$(SRC_DIR)

$(OUT_DIR)/types.o: $(SEMANTIC_DIR)/types.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/types.c -o $(OUT_DIR)/types.o -I$(SRC_DIR)

$(OUT_DIR)/constructor_analysis.o: $(SEMANTIC_DIR)/constructor_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/constructor_analysis.c -o $(OUT_DIR)/constructor_analysis.o -I$(SRC_DIR)

$(OUT_DIR)/control_expr_analysis.o: $(SEMANTIC_DIR)/control_expr_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/control_expr_analysis.c -o $(OUT_DIR)/control_expr_analysis.o -I$(SRC_DIR)

$(OUT_DIR)/lhs_analysis.o: $(SEMANTIC_DIR)/lhs_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/lhs_analysis.c -o $(OUT_DIR)/lhs_analysis.o -I$(SRC_DIR)

$(OUT_DIR)/logic_expr_analysis.o: $(SEMANTIC_DIR)/logic_expr_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/logic_expr_analysis.c -o $(OUT_DIR)/logic_expr_analysis.o -I$(SRC_DIR)

$(OUT_DIR)/math_expr_analysis.o: $(SEMANTIC_DIR)/math_expr_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/math_expr_analysis.c -o $(OUT_DIR)/math_expr_analysis.o -I$(SRC_DIR)

$(OUT_DIR)/func_call_analysis.o: $(SEMANTIC_DIR)/func_call_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/func_call_analysis.c -o $(OUT_DIR)/func_call_analysis.o -I$(SRC_DIR)

$(OUT_DIR)/built_in_analysis.o: $(SEMANTIC_DIR)/built_in_analysis.c $(SRC_DIR)/semantic.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SEMANTIC_DIR)/built_in_analysis.c -o $(OUT_DIR)/built_in_analysis.o -I$(SRC_DIR)

#Gen_func.o
$(OUT_DIR)/gen_func.o: $(SRC_DIR)/gen_func.c $(SRC_DIR)/gen.h
	cc -g -c $(SRC_DIR)/gen_func.c -o $(OUT_DIR)/gen_func.o -I$(SRC_DIR)

#Gen.o
$(OUT_DIR)/gen.o: $(SRC_DIR)/gen.c $(SRC_DIR)/gen.h
	cc -g -c $(SRC_DIR)/gen.c -o $(OUT_DIR)/gen.o -I$(SRC_DIR)

#Print_code.o
$(OUT_DIR)/print_code.o: $(SRC_DIR)/print_code.c $(SRC_DIR)/gen.h
	cc -g -c $(SRC_DIR)/print_code.c -o $(OUT_DIR)/print_code.o -I$(SRC_DIR)

#Virtual_machine.o
$(OUT_DIR)/virtual_machine.o: $(SRC_DIR)/virtual_machine.c $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(SRC_DIR)/virtual_machine.c -o $(OUT_DIR)/virtual_machine.o -I$(SRC_DIR)

# Regole per gli script della macchina virtuale (da instructions/)
$(OUT_DIR)/arithmetic.o: $(INSTR_DIR)/arithmetic.c $(SRC_DIR)/virtual_machine.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(INSTR_DIR)/arithmetic.c -o $(OUT_DIR)/arithmetic.o -I$(SRC_DIR)

$(OUT_DIR)/built_in.o: $(INSTR_DIR)/built_in.c $(SRC_DIR)/virtual_machine.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(INSTR_DIR)/built_in.c -o $(OUT_DIR)/built_in.o -I$(SRC_DIR)

$(OUT_DIR)/comparison.o: $(INSTR_DIR)/comparison.c $(SRC_DIR)/virtual_machine.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(INSTR_DIR)/comparison.c -o $(OUT_DIR)/comparison.o -I$(SRC_DIR)

$(OUT_DIR)/flow.o: $(INSTR_DIR)/flow.c $(SRC_DIR)/virtual_machine.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(INSTR_DIR)/flow.c -o $(OUT_DIR)/flow.o -I$(SRC_DIR)

$(OUT_DIR)/io.o: $(INSTR_DIR)/io.c $(SRC_DIR)/virtual_machine.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(INSTR_DIR)/io.c -o $(OUT_DIR)/io.o -I$(SRC_DIR)

$(OUT_DIR)/logical.o: $(INSTR_DIR)/logical.c $(SRC_DIR)/virtual_machine.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(INSTR_DIR)/logical.c -o $(OUT_DIR)/logical.o -I$(SRC_DIR)

$(OUT_DIR)/vars.o: $(INSTR_DIR)/vars.c $(SRC_DIR)/virtual_machine.h $(SRC_DIR)/gen.h $(SRC_DIR)/def.h
	cc -g -c $(INSTR_DIR)/vars.c -o $(OUT_DIR)/vars.o -I$(SRC_DIR)

# Comando clean
clean:
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/lexer.c $(OUT_DIR)/parser.c \
	      $(OUT_DIR)/parser.h $(OUT_DIR)/parser.output compiler

.PHONY: clean