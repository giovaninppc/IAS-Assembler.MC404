/*Giovani Nascimento Pereira - 16809
 *Mudulo para implementação de Lista .c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


/*Create a new Node from the passed values*/
Node newNode(string s, address value){
	Node a;
	a = malloc(sizeof(List));
	a->value = value.ad;
	strcpy(a->info, s);
	a->next = NULL;
	a->left = value.left;
	return a;
}

/*Inset a information node on the List*/
void insertList(Head *head, string s, address value){

	if(*head == NULL){
		*head = newNode(s, value);
		return;
	}

	Node node = *head;
	while(node->next != NULL){
		node = node->next;
	}

	node->next = newNode(s, value);

}

/*Start a List with a Null pointer*/
Node startList(){
	return NULL;
}

/*Find a Node with the specifyed Sting
 *and return a pointer to that node
 *if not compatible, return NULL*/
Node findStringList (Head head, string s){

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

void removeList(){


}

/*Free the memoty allocated by the List*/
void deleteList(Head head){

	Node node1 = head, node2;

	while(node1 != NULL){
		node2 = node1;
		node1 = node1->next;
		free(node2);
	}

}

/*Print a List on stdout*/
void printList(Head head){

	Node node = head;

	while(node != NULL){
		printf("%s %d left: %d\n", node->info, node->value, node->left);
		node = node->next;
	}

}
