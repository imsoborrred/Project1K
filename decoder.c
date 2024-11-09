#include <stdio.h>
#include "decoder.h"

void decodeInstruction(const char *line)
{

    char J = line[0];
    char C = line[1];
    char D1 = line[2];
    char D0 = line[3];
    char Sreq = line[4];
    char S = line[5];
    char imm2 = line[5];
    char imm1 = line[6];
    char imm0 = line[7];

    printf("Decoded bits from instruction:\n");
    printf("J= %c\n", J);
    printf("C= %c\n", C);
    printf("D1= %c\n", D1);
    printf("D0= %c\n", D0);
    printf("Sreq= %c\n", Sreq);
    printf("S= %c\n", S);
    printf("Imm2= %c\n", imm2);
    printf("Imm1= %c\n", imm1);
    printf("Imm0= %c\n", imm0);
}
