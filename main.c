/*Giovani Nascimento Pereira - 168609
 *Projeto MC404 - Montador IAS*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "exit.h"


/*Begining the Main function*/
int main(int argc, char *argv[]){

	string nameFile;
	FILE *source;
	string map[1024];

	for(int i=0; i<1024; i++)
		map[i][0] = 0;

	/* writeMode is a flag
	 * it marks if the exit will be
	 * stdout = false
	 * FILE = true*/
	bool writeMode = false;

	/*Structure to store labels*/
	Head labels = startList();

	/*Checking the valid parameters and defining the writing mode*/
	if(argc <= 1){
		return 0; /*No input FILE is given*/
	}
	if(argc > 2){
		writeMode = true; //Output file is given
	}

	/*Opening FILE to use*/
	strcpy(nameFile, argv[1]);
	source = fopen(nameFile, "r");
	if(source == NULL){
		printf("houve um erro na abertura do arquivo\n");
		return 1;
	}

	/*Getting Labels*/
	getLabels(source, &labels);
	rewind(source);

	/*reating Memory Map*/
	createMemorymap(source, labels, map);

	/*Printing Answer*/
	out(map, writeMode);


	deleteList(labels);
	fclose(source);

	return 0;
}