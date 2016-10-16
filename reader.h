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
void addSet(FILE *source, Head *labels);
void removeDots(string s);
bool checkSym(string s);
void getNextWord(string word, string row, int *i);
//void checkMisplacedLabels(FILE *source, Head labels);

#endif