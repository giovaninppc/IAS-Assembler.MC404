/*Giovani Nascimento Pereira - 168609
 *Modulo para impressao da saida do Montador
 *ele verifica se houve erro, caso sim ñao imprime o mapa de memoria*/

#include <stdio.h>
#include <string.h>
#include "text.h"
#include "exit.h"

/*Function out: print the answer
 (Memory map or ERROR message)
 on the correct output:
 writeMode == true => archive
 writeMode == false => stdout*/
void out(string *map, int writeMode, FILE *output){

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