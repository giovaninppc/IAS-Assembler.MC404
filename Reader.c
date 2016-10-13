/*Giovani Nascimento Pereira - 168609
 *Modulo para auxilio na leitura de arquivos*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bool.h"
#include "Text.h"
#include "Reader.h"

void finishLine (FILE *source){

	char kill;
	do{
		fscanf(source, "%c", &kill);
	}while(kill != '\n');

}

/*Checkif a word passed by parameter is a valid Label
 *valid labels end with ':' character*/
bool checkLabel(string s){

	int size = strlen(s);
	
	if(s[size-1] == ':')
		return true;

	return false;
}