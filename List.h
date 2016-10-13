/*Giovani Nasciment Pereira - 168609
 * Modulo Lista.h*/

#ifndef _Library
#define _Library

#include "Text.h"

typedef struct List{

	string info;
	int value;
	bool left;
	struct List *next;

} List;

typedef struct List* Node;
typedef struct List* Head;

typedef struct address{
	int ad;
	bool left;
}address, Address;

void insertList(Head *head, string s, address value);
Node findStringList (Head head, string s);
void deleteList(Head head);
void printList(Head head);
Node newNode(string s, address value);
Node startList();
void removeList();

#endif