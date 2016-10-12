/*Giovani Nascimento Pereira - 168609
 *Projeto MC404 - Montador IAS*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Reader.h"
#include "Bool.h"
#include "Text.h"
#include "List.h"

void finishLine (FILE *source){

	char kill;
	do{
		fscanf(source, "%c", &kill);
	}while(kill != '\n');

}


/*Begining the Main function*/
int main(int argc, char *argv[]){

	string nameFile;
	FILE *source;
	string word;

	/* writeMode is a flag
	 * it marks if the exit will be
	 * stdout = false
	 * FILE = true*/
	bool writeMode = false;

	/*Checking the valid parameters and defining the writing mode*/
	if(argc <= 1){
		return 1; /*No input FILE is given*/
	}
	if(argc >= 2){
		writeMode = true;
	}

	/*Opening FILE to use*/
	strcpy(nameFile, argv[1]);
	source = fopen(nameFile, "r");


	/*Getting Rotules*/
	while(fscanf(source, " %s", word) != EOF){
		
		/*Passing Comment*/
		if(word[0] == '#'){
			finishLine(source);
			continue;
		}
		/*dbbg*/printf("%s\n", word);

	}

	rewind(source);

	/*dbbg*/printf("%d", writeMode);

	fclose(source);

	return 0;
}