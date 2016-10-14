/*Giovani Nascimento Pereira - 168609
 *Modulo para impressao da saida do Montador
 *ele verifica se houve erro, caso sim ñao imprime o mapa de memoria*/

#include <stdio.h>
#include <string.h>
#include "text.h"
#include "exit.h"

void out(string *map, int writeMode){

	if(writeMode == false){
		for(int i=0; strlen(map[i]) > 0; i++){
			printf("%s\n", map[i]);
		}
	}
}