/*Giovani Nascimento Pereira - 168609
 *this part is responsable for creating the memory map
 *by reading it on the FILE and saving on the proper structure
 *Modulo .h*/

#ifndef _memorymap
#define _memorymap

#include "reader.h"

void createMemorymap(FILE *source, Head *labels, string *map);
int updateAddress(string s, address *ad, FILE *source);
void writeMap(string op, string add, address ad, Head labels, string *map, int *printLine);
void writeWordOnMap(string word, address ad, string *map, int *printLine, Head labels);
bool checkDirective(string s);
void convertToStringSize3(string s, Head labels);
void convertToStringSize10(string s, Head labels);
bool checkIfHex(string s);
bool checkIfNumber(string s);
bool removeAspas(string s);
void convertToNegativeHex(string s);

#endif