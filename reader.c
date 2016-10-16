/*Giovani Nascimento Pereira - 168609
 *Modulo para auxilio na leitura de arquivos e retirada de Rotulos*/

#include "reader.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "exit.h"

/*Finishes reading a line from the given FILE*/
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
	
	if(s[size-1] == ':'){
		
		for(int i=0; i<size-1; i++){
			if(ispunct(s[i])){
				//Label not valid
				return false;
			}
		}
		return true;
	}

	return false;
}

/*Start an adress on the 000 left position*/
void startAddress(address *a){
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
			//printf("%s %d\n", orgSize, (int)strlen(orgSize));
			(*ad).ad = convertNumber(orgSize);
			(*ad).left = 1;
			return;
		}
		else if (strcmp(s, ".wfill") == 0){
			//wfill, falta considerar o hexadecimal
			string wfillSize;
			fscanf(source, " %s", wfillSize);
			//printf("%s %d\n", wfillSize, (int)strlen(wfillSize));
			(*ad).ad = ad->ad + convertNumber(wfillSize);
			fscanf(source, " %s", wfillSize); //read the value after the wfillSize
			return;
		}
		else if (strcmp(s, ".align") == 0){
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
		else if(strcmp(s, ".set")){
			//It doesnt jump addresses, but its not an error
			return;
		}
		else {
			//DIRETIVA INVALIDA
		}
	}

	//Checking for regular commands
	//Load commands
	else if(checkRegularCommand(s)){
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
		int exit = 0;
		for(int i=position-1, x=1; i>=2; i--, x*=16){
			if(s[i] >= '0' && s[i] <= '9'){
				exit += (int) x * (s[i] - '0');
			}
			else{
				switch (s[i]){
					case 'A':
						exit += (int) x * (10);
						break;
					case 'B':
						exit += (int) x * (11);
						break;
					case 'C':
						exit += (int) x * (12);
						break;
					case 'D':
						exit += (int) x * (13);
						break;
					case 'E':
						exit += (int) x * (14);
						break;
					case 'F':
						exit += (int) x * (15);
						break;
					default:
						//ERROR
						addERROR("Invalid number reference", s);
						break;
				}
			}
		}
		return exit;
	}

	//if decimal number
	int exit = 0;
	int k = 0;
	if(s[0] == '-'){
		k++;
	}
	for(int i=position-1, x=1; i>=k; i--, x*=10){
		exit += (int) x * (s[i] - '0');
	}
	if(k){
		return -1*exit;
	}
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

/*Add a .set on the given list os parameters*/
void addSet(FILE *source, Head *labels){

	string set, number;
	fscanf(source, " %s", set);
	fscanf(source, " %s", number);
	if(checkSym(set) == false){
		//ERROR
		addERROR("Not a valid .set Sym", set);
		return;
	}
	if(checkIfNumber(number) == false && checkIfHex(number) == false){
		//ERROR
		addERROR("Wrong parameters on .set directive", number);
	}
	Address a;
	a.ad = convertNumber(number);
	a.left = -1;
	insertList(labels, set, a);
}

/*Check if a given string does not contais symbols*/
bool checkSym(string s){
	int size = strlen(s);
	for(int i=0; i<size; i++){
		if(isalnum(s[i]) == 0){
			return false;
		}
	}
	return true;
}

/*Get the labels from the document*/
void getLabels(FILE *source, Head *labels){
	
	string word;
	address place;
	char kill = '\n', use;
	int line = 1;
	bool lineLabel = false;

	startAddress(&place);

	while(fscanf(source, " %s", word) != EOF){

		//Getting the last caracter, if its a line breaker, add 1 line		
		fscanf(source, "%c", &kill);
		use = kill;
		while(use == ' ' || use == '\t'){
			fscanf(source, "%c", &use);
		}
		if(use == '\n'){
			kill = use;
		}
		fseek(source, -1*sizeof(char), SEEK_CUR);

		/*Passing Comment*/
		if(word[0] == '#'){
			finishLine(source);
			lineLabel = false;
			continue;
		}

		//Change the addres depending on the command
		changeAddress(word, &place, source);

		//Verify if the word given is actually a label
		if(checkLabel(word)){

			//Checking if its the only label on this line
			if(lineLabel == true){
				//ERROR
				addERROR("More than 1 label on the line", word);
				return;
			}

			lineLabel = true;
			removeDots(word);
			insertList(labels, word, place);
		}

		if(strcmp(word, ".set") == 0){
			addSet(source, labels);
		}

		if(strcmp(word, ".word") == 0){
			string x;
			fscanf(source, " %s", x);
			/*Node a = findStringList(*labels, x);
			if(checkIfNumber(x)==false && checkIfHex(x)==false 
				&& (a==NULL || a->left == -1) ){
				//ERROR
				addERROR("Invalid parameter on .word directive" , x);
			}*/
			lineLabel = false;
			fscanf(source, "%c", &kill);
		}

		if(kill == '\n'){
			line++;
			lineLabel = false;
		}
	}
}

/*Remove te caracter : at the end of a string*/
void removeDots(string s){
	int size = strlen(s);
	if(s[size-1] == ':'){
		s[size-1] = 0;
	}
}