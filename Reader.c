/*Giovani Nascimento Pereira - 168609
 *Modulo para auxilio na leitura de arquivos*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Text.h"
#include "Reader.h"

void finishLine (FILE *source){

	char kill;
	do{
		fscanf(source, "%c", &kill);
	}while(kill != '\n');

}