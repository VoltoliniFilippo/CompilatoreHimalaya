#include <stdio.h>
#include "gen.h"

char* operators[] = 
{
  "HCOD",
  "VARS",
  "HALT",
  "VALL",
  "LOCI",
  "LOCR",
  "LOCS",
  "LOAD",
  "GROU",
  "RNGE",
  "LODA",
  "INLD",
  "CIDX",
  "IXAD",
  "STOR",
  "SKIP",
  "SKPF",
  "EQUA",
  "NEQU",
  "GTHI",
  "GEQI",
  "LTHI",
  "LEQI",
  "GTHR",
  "GEQR",
  "LTHR",
  "LEQR",
  "GTHS",
  "GEQS",
  "LTHS",
  "LEQS",
  "BLNG",
  "ADDI",
  "SUBI", 
  "MULI",
  "DIVI",
  "ADDR",
  "SUBR",
  "MULR",
  "DIVR",
  "NEGI",
  "NEGR",
  "NEGB",
  "TORE",
  "TOIN",
  "EMPT",
  "HEAD",
  "TAIL",
  "CARD",
  "READ",
  "WRTE",
  "WRTL",
  "PUSH",
  "JUMP",
  "APOP",
  "FUNC",
  "RETN"
};

void print_generated_code(Code code){
    Stat *stat = code.head;

    while(stat != NULL){
        printf("%s ", operators[(int)(stat->op)]);
        print_args(stat->op, stat->args);
        stat = stat->next;
    }
}

void print_args(Operator op, Value args[3]){
    switch(op){
        case HALT:
        case RNGE:
        case CIDX:
        case STOR:
        case EQUA:
        case NEQU:
        case GTHI:
        case GEQI:
        case LTHI:
        case LEQI:
        case GTHR:
        case GEQR:
        case LTHR:
        case LEQR:
        case GTHS:
        case GEQS:
        case LTHS:
        case LEQS:
        case BLNG:
        case ADDI:
        case SUBI:
        case MULI:
        case DIVI:
        case ADDR:
        case SUBR:
        case MULR:
        case DIVR:
        case NEGI:
        case NEGR:
        case NEGB:
        case TORE:
        case TOIN:
        case EMPT:
        case HEAD:
        case TAIL:
        case CARD:
        case APOP:
        case RETN:
            printf("\n");
            break;

        case HCOD:
        case LOCI:
        case IXAD:
        case SKIP:
        case SKPF:
        case PUSH:
        case JUMP:
        case FUNC:
        case VARS:
            printf("%d\n", args[0].ival);
            break;

        case VALL:
        case LOAD:
        case LODA:
        case INLD:
            printf("%d %d\n", args[0].ival, args[1].ival);
            break;

        case GROU:
            printf("%d %d %d\n", args[0].ival, args[1].ival, args[2].ival);
            break;

        case READ:
            printf("%d %s\n", args[0].ival, args[1].sval);
            break;
        
        case LOCS:
        case WRTE:
        case WRTL:
            printf("%s\n", args[0].sval);
            break;

        case LOCR:
            printf("%f\n", args[0].rval);
            break;

        default:
            printf("Codice non riconosciuto\n");
    }
}