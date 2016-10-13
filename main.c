/*Giovani Nascimento Pereira - 168609
 *Projeto MC404 - Montador IAS*/

#include "Header.h"

/*Begining the Main function*/
int main(int argc, char *argv[]){

	string nameFile;
	FILE *source;
	string word;
	int address = 0;

	/* writeMode is a flag
	 * it marks if the exit will be
	 * stdout = false
	 * FILE = true*/
	bool writeMode = false;

	/*Structure to store labels*/
	Head labels = startList();

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

		//Verify if the word given is actually a label
		if(checkLabel(word) == true){
			insertList(&labels, word, address);

			/*dbbg*/printList(labels);
		}
	}

	rewind(source);

	/*dbbg*/printf("%d", writeMode);

	deleteList(labels);

	fclose(source);

	return 0;
}