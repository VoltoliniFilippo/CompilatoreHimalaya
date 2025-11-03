#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "gen.h"

int code_size(Code code){
    int n = 0;
    Stat *pt = code.head;

    while (pt != NULL) {
        n++;
        pt = pt->next;
    }

    return n;
}

void relocate(Code code, int offset) {
    if (code.head == NULL) return;
    Stat *pt = code.head;
    int i;

    for(i = 1; i <= code.size && pt != NULL; i++) {
        pt->address += offset;
        pt = pt->next;
    }
}

Code appcode(Code code1, Code code2) {
    Code rescode;

    if (code1.head == NULL)
        return code2;

    if (code2.head == NULL) 
        return code1;

    relocate(code2, code1.size);
    rescode.head = code1.head;
    rescode.tail = code2.tail;
    code1.tail->next = code2.head;
    rescode.size = code1.size + code2.size;
    return rescode;
}

Code endcode(){
    static Code code = {NULL, 0, NULL};
    return code;
}

Code concode(Code code1, Code code2, ...) {
    Code rescode = code1;
    va_list args;
    Code next_code;

    va_start(args, code2);
    next_code = code2;

    while (next_code.head != NULL) {
        rescode = appcode(rescode, next_code);
        next_code = va_arg(args, Code);
    }

    va_end(args);
    return rescode;
}

Stat *newstat(Operator op){
    Stat *pstat;
        
    pstat = (Stat*)malloc(sizeof(Stat));
    pstat->address = 0;
    pstat->op = op;
    pstat->next = NULL;
    return pstat;
}

Code makecode(Operator op){
    Code code;
        
    code.head = code.tail = newstat(op);
    code.size = 1;
    return code;
}

Code makecode1(Operator op, int arg){
    Code code;
        
    code = makecode(op);
    code.head->args[0].ival = arg;
    return code;
}

Code makecode2(Operator op, int arg1, int arg2){
    Code code;
    
    code = makecode(op);
    code.head->args[0].ival = arg1;
    code.head->args[1].ival = arg2;
    return code;
}

Code makecode3(Operator op, int arg1, int arg2, int arg3){
    Code code;
    
    code = makecode(op);
    code.head->args[0].ival = arg1;
    code.head->args[1].ival = arg2;
    code.head->args[2].ival = arg3;
    return code;
}

Code make_func_call(int numparams, int entry){
    Code code1 = appcode(makecode1(PUSH, numparams), makecode1(JUMP, entry));
    Code code2 = appcode(makecode(APOP), endcode());
    return appcode(code1, code2);
}

Code makecode_str(Operator op, char *arg){
    Code code;

    code = makecode(op);
    code.head->args[0].sval = arg;
    return code;
}

Code make_vall(int size, int num){
    return makecode2(VALL, size, num);
}

Code make_loci(int value){
    return makecode1(LOCI, value);
}

Code make_locr(float value){
    Code code;

    code = makecode(LOCR);
    code.head->args[0].rval = value;
    return code;
}

Code make_locs(char *value){
    return makecode_str(LOCS, value);
}

Code make_load(int env, int oid){
    return makecode2(LOAD, env, oid);
}

Code make_loda(int env, int oid){
    return makecode2(LODA, env, oid);
}

Code make_struct_grou(int fields, int size){
    return makecode3(GROU, fields, size, 1);
}

Code make_vect_grou(int fields, int size, int elements){
    return makecode3(GROU, fields, size, elements);
}

Code make_inld(int offset, int size){
    return makecode2(INLD, offset, size);
}

Code make_fielding(int env, int oid, int offset, int size){
    return concode(make_load(env, oid), make_inld(offset, size), endcode());
}

Code make_read(int oid, char *format){
    Code code;

    code = makecode(READ);
    code.head->args[0].ival = oid;
    code.head->args[1].sval = format;
    return code;
}

Code make_ixad(int scale){
    return makecode1(IXAD, scale);
}

Code make_indexing(int scale, int offset, int size){
    return concode(makecode(CIDX), make_ixad(scale), make_inld(offset, size), endcode());
}

Code make_write(char *format){
    return makecode_str(WRTE,format);
}

Code make_writeln(char *format){
    return makecode_str(WRTE,format);
}

Code make_skip_exit(Operator op, int expr){
    return makecode1(op, expr + 1);
}

Code make_skip_offset(Operator op, int expr){
    return makecode1(op, expr + 2);
}

Code make_skip_up(Operator op, int expr){
    return makecode1(op, -expr);
}

Code make_func(int fid){
    return makecode1(FUNC, fid);
}

Code make_vars(int n){
    return makecode1(VARS, n);
}

Code make_hcod(int size){
    return makecode1(HCOD, size);
}