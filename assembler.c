#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assembler.h"

void assembler(const char *inputFile, const char *outputFile)
{
    FILE *fp = fopen(inputFile, "r");
    FILE *fp2 = fopen(outputFile, "w");
    char line[50];
    int lineNum = 1;

    printf("Starting Assembler...\n");
    printf("Reading file: %s\n", inputFile);

    if (fp == NULL)
    {
        printf("File %s not found!\n", inputFile);
        return;
    }
    if (fp2 == NULL)
    {
        printf("Could not open output file %s!\n", outputFile);
        fclose(fp);
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line, "\n")] = 0;

        char command[50];
        int j = 0;
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] != ' ')
            {
                command[j++] = line[i];
            }
        }
        command[j] = '\0';

        if (strlen(command) == 0)
        {
            printf("Error: Empty instruction line\n");
            continue;
        }
        if (strlen(command) > 20)
        {
            printf("Error: Instruction too long\n");
            continue;
        }

        const char *machineCode = NULL;

        if (strcmp(command, "RA=RA+RB") == 0)
        {
            machineCode = "00000000";
        }
        else if (strcmp(command, "RB=RA+RB") == 0)
        {
            machineCode = "00010000";
        }
        else if (strcmp(command, "RA=RA-RB") == 0)
        {
            machineCode = "00000100";
        }
        else if (strcmp(command, "RB=RA-RB") == 0)
        {
            machineCode = "00010100";
        }
        else if (strcmp(command, "RO=RA") == 0)
        {
            machineCode = "00100000";
        }
        else if (strncmp(command, "RA=", 3) == 0)
        {
            int imm = atoi(command + 3);
            switch (imm)
            {
            case 0:
                machineCode = "00001000";
                break;
            case 1:
                machineCode = "00001001";
                break;
            case 2:
                machineCode = "00001010";
                break;
            case 3:
                machineCode = "00001011";
                break;
            case 4:
                machineCode = "00001100";
                break;
            case 5:
                machineCode = "00001101";
                break;
            case 6:
                machineCode = "00001110";
                break;
            case 7:
                machineCode = "00001111";
                break;
            default:
                printf("Uncategorized immediate value for RA: %d\n", imm);
                break;
            }
        }
        else if (strncmp(command, "RB=", 3) == 0)
        {
            int imm = atoi(command + 3);
            switch (imm)
            {
            case 0:
                machineCode = "00011000";
                break;
            case 1:
                machineCode = "00011001";
                break;
            case 2:
                machineCode = "00011010";
                break;
            case 3:
                machineCode = "00011011";
                break;
            case 4:
                machineCode = "00011100";
                break;
            case 5:
                machineCode = "00011101";
                break;
            case 6:
                machineCode = "00011110";
                break;
            case 7:
                machineCode = "00011111";
                break;
            default:
                printf("Uncategorized immediate value for RB: %d\n", imm);
                break;
            }
        }
        else if (strncmp(command, "JC=", 3) == 0)
        {
            int imm = atoi(command + 3);
            switch (imm)
            {
            case 0:
                machineCode = "01110000";
                break;
            case 1:
                machineCode = "01110001";
                break;
            case 2:
                machineCode = "01110010";
                break;
            case 3:
                machineCode = "01110011";
                break;
            case 4:
                machineCode = "01110100";
                break;
            case 5:
                machineCode = "01110101";
                break;
            case 6:
                machineCode = "01110110";
                break;
            case 7:
                machineCode = "01110111";
                break;
            default:
                printf("Uncategorized immediate value for JC: %d\n", imm);
                break;
            }
        }
        else if (strncmp(command, "J=", 2) == 0)
        {
            int imm = atoi(command + 2);
            switch (imm)
            {
            case 0:
                machineCode = "10110000";
                break;
            case 1:
                machineCode = "10110001";
                break;
            case 2:
                machineCode = "10110010";
                break;
            case 3:
                machineCode = "10110011";
                break;
            case 4:
                machineCode = "10110100";
                break;
            case 5:
                machineCode = "10110101";
                break;
            case 6:
                machineCode = "10110110";
                break;
            case 7:
                machineCode = "10110111";
                break;
            default:
                printf("Uncategorized immediate value for J: %d\n", imm);
                break;
            }
        }
        else
        {
            printf("Error: Invalid instruction format: %s\n", command);
        }

        if (machineCode != NULL)
        {
            printf("Line %d: %s -> Machine Code: %s\n", lineNum, command, machineCode);
            fprintf(fp2, "%s\n", machineCode);
        }

        lineNum++;
    }

    printf("Successfully generated output file: %s\n", outputFile);
    fclose(fp);
    fclose(fp2);
}