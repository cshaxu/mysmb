#ifndef MINE_NUMBER_H
#define MINE_NUMBER_H
/* Formats a signed 16-bit game value with optional zero padding. Caller owns
 * at least eight bytes. Avoids platform varargs/Win16 CRT formatting ABIs. */
char *mine_number(char *out,int value,int minimum);
#endif
