/*Giovani Nascimento Pereira - 168609
 *this part is responsable for creating the memory map
 *by reading it on the FILE and saving on the proper structure
 *Modulo .h*/

#ifndef _memorymap
#define _memorymap

#include "text.h"

typedef struct Memorymap{

	string ad;
	string OP1;
	string p1;
	string OP2;
	string p2;

	struct Memorymap *next;
}Memorymap, memorymap;

#endif