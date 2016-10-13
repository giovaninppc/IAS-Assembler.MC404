/*Giovani Nascimento Pereira - 168609
 *Modulo para auxilio na leitura de arquivos e retirada de Rotulos*/

#include "Reader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

/*Start an adress on the 000 left position*/
void startAdress(address *a){
	a->ad = 0;
	a->left = true;
}

/*This function recieves a word and an address
  And alter the value of the address*/
void changeAddress(string s, address *ad, FILE *source){

	//Checking for directives wich may change the position
	if(s[0] == '.'){
		if(strcmp(s, ".word") == 0){
			(*ad).ad = ad->ad + 1;
			return;
		}
		else if (strcmp(s, ".org") == 0){
			string orgSize;
			fscanf(source, " %s", orgSize);
			printf("%s %d\n", orgSize, (int)strlen(orgSize));
			(*ad).ad = convertNumber(orgSize);
			return;
		}
		else if (strcmp(s, ".wfill") == 0){
			//wfill, falta considerar o hexadecimal
			string wfillSize;
			fscanf(source, " %s", wfillSize);
			printf("%s %d\n", wfillSize, (int)strlen(wfillSize));
			(*ad).ad = ad->ad + convertNumber(wfillSize);
			return;
		}
		else if (strcmp(s, ".allign") == 0){
			int allign;
			fscanf(source, "%d", &allign);
			if(ad->left == false){
				(*ad).ad = ad->ad + 1;
				(*ad).left = true;
			}
			if(ad->ad % allign != 0){
				(*ad).ad = ad->ad + allign - (ad->ad % allign);
			}
			return;
		}
	}

	//Checking for regular commands
	//Load commands
	if(checkRegularCommand(s)){
		oneStep(ad);
	}

}

/*Check if the command given by paameter is a valid command mnemonic*/
bool checkRegularCommand(string s){
	if(strcmp(s, "LD")==0 || strcmp(s, "LD-")==0 || strcmp(s, "LD|")==0 || 
		strcmp(s, "LDmq")==0 || strcmp(s, "LDmq_mx")==0 || strcmp(s, "ST")==0 || 
		strcmp(s, "STaddr")==0 || strcmp(s, "LSH")==0 || strcmp(s, "RSH")==0 || 
		strcmp(s, "JMP")==0 || strcmp(s, "ADD")==0 || strcmp(s, "SUB")==0 || 
		strcmp(s, "ADD|")==0 || strcmp(s, "SUB|")==0 || strcmp(s, "DIV")==0 || 
		strcmp(s, "MUL")==0 || strcmp(s, "JUMP+")==0){
		return true;
	}
	return false;
}

/*Convert a String into a int type number*/
int convertNumber(string s){

	int position = (int)strlen(s);

	//if hexadecimal number
	if(s[0] == '0' && s[1] == 'x'){
		//CONVERSAO DE HEXADECIMAL EM DECIMAL
		return 0;
	}

	//if decimal number
	int exit = 0;
	for(int i=position-1, x=1; i>=0; i--, x*=10){
		exit += (int) x * (s[i] - '0');
	}
	/*dbbg*/printf("VALOR CONVERTIDO: %d\n", exit);
	return exit;
}

/*Move one step forward on the address given by parameter*/
void oneStep(address *ad){
	if(ad->left == true){
			(*ad).left = false;
			return;
		}
		else if(ad->left == false){
			(*ad).left = true;
			(*ad).ad = ad->ad + 1;
			return;
	}
}

/*Get the labels from the document*/
void getLabels(FILE *source, Head *labels){
	
	string word;
	address place;

	startAdress(&place);

	while(fscanf(source, " %s", word) != EOF){

			/*Passing Comment*/
			if(word[0] == '#'){
				finishLine(source);
				continue;
			}
			/*dbbg*/printf("%s %d\n", word, (int)strlen(word));

			//Change the addres depending on the command
			changeAddress(word, &place, source);

			//Verify if the word given is actually a label
			if(checkLabel(word)){
				insertList(labels, word, place);
			}
	}
}