/*Giovani Nascimento Pereira - 168609
 Modulo .h de exit, contem funcoes para saida do montador e impressao de erros*/

#ifndef _exit
#define _exit

#include "memorymap.h"

void out(string *map, int writeMode, FILE *output, FILE *source);
void addERROR(string message, string error);
bool getERRORvalue();
int getLineERROR(FILE *source, string s);

#endif