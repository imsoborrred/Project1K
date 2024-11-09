#include <stdio.h>

char RA = 0;
char RB = 0;
char R0 = 0;
char result = 0;
char seen13 = 0;
char seenFirstZero = 0;

char alu(char S, char mode)
{
    if (S == 0)
    {
        result = RA + RB;

        if (mode == 'S')
        {
            if (result > 21)
            {
                return -1;
            }
        }
        else
        {
            if (result > 15)
            {
                result &= 0x0F; // Wrap around to 4 bits
            }

            if (result == 13)
            {
                seen13 = 1;
            }
            else if (seen13 && result == 0)
            {
                seenFirstZero = 1;
            }
            else if (seenFirstZero && result == 2) // Stop after showing 0,1,1,2
            {
                return -1;
            }
        }
    }
    else
    {
        result = RA - RB;
    }
    return result;
}
