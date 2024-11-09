#include <stdio.h>
#include <string.h>
#include "loader.h"

int loadInstruction(const char *inputFile, char *line, int PC)
{
    FILE *file = fopen(inputFile, "rb");
    if (file == NULL)
    {
        printf("Error: Failed to open file\n");
        return 0;
    }

    char buffer[10];
    int currentLine = 0;

    // Read until we find the instruction at PC
    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) < 8)
        {
            continue;
        }

        if (currentLine == PC)
        {
            strncpy(line, buffer, 8);
            line[8] = '\0';
            fclose(file);
            return 1;
        }

        currentLine++;
    }

    fclose(file);
    return 0;
}