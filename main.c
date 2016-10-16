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
	FILE *source = NULL, *output = NULL;
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
	//Output file is given / Opening File
	if(argc > 2){
		writeMode = true;
	}

	/*Opening FILE to use*/
	strcpy(nameFile, argv[1]);
	source = fopen(nameFile, "r");
	if(source == NULL){
		printf("houve um erro na abertura do arquivo de entrada\n");
		return 1;
	}

	/*Opening Out File*/
	if(writeMode == true && output == NULL){
		string outputFile;
		strcpy(outputFile, argv[2]);
		output = fopen(outputFile, "w");
		
		if(outputFile == NULL){
			printf("houve um erro na abertura do arquivo de saída\n");
			return 1;
		}
	}

	/*Getting Labels*/
	getLabels(source, &labels);
	rewind(source);

//printList(labels);

	/*reating Memory Map*/
	if(getERRORvalue() == false){
		createMemorymap(source, &labels, map);
	}

	/*Printing Answer*/
	out(map, writeMode, output, source);

	/*Freeing alocatted memory and closing files*/
	deleteList(labels);
	fclose(source);

	return 0;
}