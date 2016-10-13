/*Giovani Nascimento Pereira - 168609
 *Modulo .h do Reader*/

#ifndef _reader
#define _reader

#include <stdio.h>
#include "Bool.h"
#include "Text.h"
#include "List.h"


typedef struct address{
	int ad;
	bool left;
}address, Address;


void finishLine (FILE *source);
bool checkLabel(string s);
void getLabels(FILE *source, Head *labels);
void oneStep(address *ad);

#endif