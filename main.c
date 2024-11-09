#include <stdio.h>
#include <string.h>
//#include <unistd.h>  
#include "loader.h"
#include "mux.h"
#include "alu.h"
#include "assembler.h"
#include "d0d1.h"

extern char RA;
extern char RB;
extern char RO;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char instruction[9];
    int PC = 0;
    int instructionsExecuted = 0;

    char *ext = strrchr(argv[1], '.');
    if (ext && strcmp(ext, ".asm") == 0)
    {
        assembler(argv[1], "fibonacci.bin");
    }
    else
    {
        char mode;
        printf("Select one of the following mode\n");
        printf("R - Run in continuous mode\n");
        printf("S - Run step-by-step\n");
        printf("Select mode:");
        scanf(" %c", &mode);

        printf("Loading binary file: %s\n", argv[1]);
        printf("Starting Simulator in %s mode...\n",
               mode == 'S' ? "step-by-step" : "continuous");

        while (loadInstruction(argv[1], instruction, PC))
        {
            char J = instruction[0] - '0';
            char C = instruction[1] - '0';
            char D1 = instruction[2] - '0';
            char D0 = instruction[3] - '0';
            char Sreq = instruction[4] - '0';
            char S = instruction[5] - '0';
            char imm = (instruction[6] - '0') * 2 + (instruction[7] - '0');

            if (mode == 'S')
            {
                const char *spacing = "      ";
                printf("Instruction %d: ", PC);

                if (strcmp(instruction, "00100000") == 0) // RO=RA
                {
                    printf("RO=RA -> RO=%d%s", (int)RA, spacing);
//                    sleep(1); // Add 1-second delay after RO=RA instruction
                }
                else if (strcmp(instruction, "00001000") == 0) // RA=0
                    printf("RA=0%s", spacing);
                else if (strcmp(instruction, "00011001") == 0) // RB=1
                    printf("RB=1%s", spacing);
                else if (strcmp(instruction, "00010000") == 0) // RB=RA+RB
                    printf("RB=RA+RB%s", spacing);
                else if (strcmp(instruction, "00000000") == 0) // RA=RA+RB
                    printf("RA=RA+RB%s", spacing);
                else if (strcmp(instruction, "00010100") == 0) // RB=RA-RB
                    printf("RB=RA-RB%s", spacing);
                else if (strcmp(instruction, "00000100") == 0) // RA=RA-RB
                    printf("RA=RA-RB%s", spacing);
                else if (strcmp(instruction, "01110000") == 0) // JC=0
                    printf("JC=0 (No Jump)%s", spacing);
                else if (strcmp(instruction, "10110010") == 0) // J=2
                    printf("J=2 (Jump to Instruction 2)%s", spacing);

                printf("[Press Enter to continue]");
                fflush(stdout);
                getchar();
                printf("\r");
            }

            char result = alu(S, mode);
            if (result == -1)
            {
                if (mode == 'S')
                    printf("Overflow detected - sequence complete\n");
                break;
            }

            char enA, enB, enO;
            registers(D0, D1, &enA, &enB, &enO);
            mux(enA, enB, enO, Sreq, imm, result, mode);

            if (J)
                PC = imm;
            else if (C && RB == 0)
                PC = imm;
            else
                PC++;

            instructionsExecuted++;
        }
    }

    return 0;
}

