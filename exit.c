/*Giovani Nascimento Pereira - 168609
 *Modulo para impressao da saida do Montador
 *ele verifica se houve erro, caso sim ñao imprime o mapa de memoria*/

#include <stdio.h>
#include <string.h>
#include "text.h"
#include "exit.h"

bool ERROR = false;
string lineERROR = "";
string ERRORmessage;

/*Function out: print the answer
 (Memory map or ERROR message)
 on the correct output:
 writeMode == true => archive
 writeMode == false => stdout*/
void out(string *map, int writeMode, FILE *output, FILE *source){

	//If an ERROR has ocourred, it doesnt print the memory map
	if(ERROR == true){

		int line;
		line = getLineERROR(source, lineERROR);

		if(writeMode == false){
			printf("ERROR on line %d\n%s\n", line, ERRORmessage);
		}
		else if(writeMode == true){
			fprintf(output, "ERROR on line %d\n%s\n", line, ERRORmessage);
		}
		return;
	}

	//Printing on stdout
	if(writeMode == false){
		for(int i=0; strlen(map[i]) > 0; i++){
			printf("%s\n", map[i]);
		}
	}

	//Print on exit archive
	else if(writeMode == true){
		for(int i=0; strlen(map[i]) > 0; i++){
			fprintf(output, "%s\n", map[i]);
		}
	}
}

/*Function called when an ERROR occours
 it recieves the ERROR string as a parameter
 and the line correspondent to the error*/
void addERROR(string message, string error){
	
	strcpy(ERRORmessage, message);
	strcpy(lineERROR, error);
	ERROR = true;

}

/*Returns the value of ERROR*/
bool getERRORvalue(){
	return ERROR;
}

/*Finds the line of a gives string on the source File*/
int getLineERROR(FILE *source, string s){

	rewind(source);
	string read;
	int line = 1;
	while(fgets(read ,65, source) != NULL){
		if(strstr(read, s) != NULL){
			return line;
		}
		line++;
	}
	return -1;
}