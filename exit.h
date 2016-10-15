/**/

#ifndef _exit
#define _exit

#include "memorymap.h"

void out(string *map, int writeMode, FILE *output);
void addERROR(string message, int line);
bool getERRORvalue();

#endif