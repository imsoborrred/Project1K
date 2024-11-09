void registers(int D0, int D1, char *enA, char *enB, char *enO)
{
    *enA = 0;
    *enB = 0;
    *enO = 0;

    // D1=0, D0=0 -> RA
    // D1=0, D0=1 -> RB
    // D1=1, D0=0 -> RO

    if (D1 == 0 && D0 == 0)
    {
        *enA = 1; // Enable Register A
    }
    else if (D1 == 0 && D0 == 1)
    {
        *enB = 1; // Enable Register B
    }
    else if (D1 == 1 && D0 == 0)
    {
        *enO = 1; // Enable Register O
    }
}