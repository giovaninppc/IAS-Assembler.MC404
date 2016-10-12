/*Giovani Nasciment Pereira - 168609
 * Modulo Lista.h*/

#ifndef _Library
#define _Library

#include <stdio.h>
#include <stdlib.h>


typedef struct List{

	string info;
	int value;
	struct List *next;

} List;

typedef struct List* Node;
typedef struct List* Head;

void InsertList(Head head, string s, int value);
Node FindStringList (Head head, string s);
void DeleteList(Head head);
void RemoveList();

#endif