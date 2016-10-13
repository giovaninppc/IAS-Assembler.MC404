#include "Header.h"

int main(){

	Head h = startList();

	insertList(&h, "1", 1);

	insertList(&h, "2", 2);

	printList(h);

	deleteList(h);

	return 0;
}