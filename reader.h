/*Giovani Nascimento Pereira - 168609
 *Modulo .h do Reader*/

#ifndef _reader
#define _reader

#include "list.h"
#include <stdio.h>
#include <stdlib.h>


void finishLine (FILE *source);
bool checkLabel(string s);
void getLabels(FILE *source, Head *labels);
void oneStep(address *ad);
int convertNumber(string s);
void startAddress(address *a);
bool checkRegularCommand(string s);

#endif