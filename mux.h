#ifndef MUX_H
#define MUX_H

extern char RA;
extern char RB;
extern char R0;

char mux(char enA, char enB, char enO, char Sreq, char imm, char alu, char mode);

#endif
