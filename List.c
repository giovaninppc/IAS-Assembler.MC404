/*Giovani Nascimento Pereira - 16809
 *Mudulo para implementação de Lista.c*/

#ifndef _Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#endif

/*Inset a information node on the List*/
void InsertList(Head head, string s, int value){

	Node node, end;

	if(head == NULL){
		head = malloc(sizeof(List));
		head->value = value;
		strcpy(head->info, s);
		return;
	}

	node = head;
	while(node->next != NULL){
		node = node->next;
	}

	end = malloc(sizeof(List));
	end = malloc(sizeof(List));
	end->value = value;
	strcpy(head->info, s);

	node->next = end;

}

/*Find a Node with the specifyed Sting
 *and return a pointer to that node
 *if not compatible, return NULL*/
Node FindStringList (Head head, string s){

	Node node;

	if(head == NULL)
		return NULL;

	node = head;

	while(node != NULL){
		if(strcmp(node->info, s) == 0){
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void RemoveList(){


}

/*Free the memoty allocated by the List*/
void DeleteList(Head head){

	Node node1 = head, node2;

	while(node1 != NULL){
		node2 = node1;
		node1 = node1->next;
		free(node2);
	}

}