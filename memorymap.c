/*Giovani Nascimento Pereira - 168609
 *this part is responsable for creating the memory map
 *by reading it on the FILE and saving on the proper structure*/

#include "memorymap.h"
#include "reader.h"
#include "text.h"
#include "list.h"
#include "exit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void createMemorymap(FILE *source, Head labels, string *map){

	string word;
	int printLine = 0;
	address ad;
	int line = 1;
	char kill;
	startAddress(&ad);

	while(fscanf(source, " %s", word) != EOF){
		
		fscanf(source, "%c", &kill);

		/*Passing Comment*/
		if(word[0] == '#'){
			finishLine(source);
			line++;
			continue;
		}

		else if(checkRegularCommand(word)){

			//LOADs
			if(strcmp(word, "LD") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("01", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "LD-") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("02", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "LD|") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("03", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "LDmq") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("0a", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "LDmq_mx") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("09", ld, ad, labels, map, &printLine);
			}

			//Position Changes
			else if(strcmp(word, "LSH") == 0){
				writeMap("14", "000", ad, labels, map, &printLine);
			}
			else if(strcmp(word, "RSH") == 0){
				writeMap("15", "000", ad, labels, map, &printLine);
			}

			//STOREs
			else if(strcmp(word, "ST") == 0){
				string st;
				fscanf(source, " %s", st);
				convertToStringSize3(st, labels);
				writeMap("21", st, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "STaddr") == 0){
				
			}

			//MATHs
			else if(strcmp(word, "ADD") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("05", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "SUB") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("06", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "ADD|") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("07", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "SUB|") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("08", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "DIV") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("0C", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "MUL") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("0B", ld, ad, labels, map, &printLine);
			}

			//JUMPs
			else if(strcmp(word, "JMP") == 0){
			}
			else if(strcmp(word, "JUMP+") == 0){
			}
		}

		else if(checkDirective(word)){
			
			if(strcmp(word, ".word") == 0){
				
				if(ad.left == false){
					//ERROR
					addERROR("Trying to add a word on the right side of memory map", line);
				}
				else{
					string w;
					fscanf(source, " %s", w);
					convertToStringSize10(w, labels);
					writeWordOnMap(w, ad, map, &printLine, labels);
					ad.ad = ad.ad +1;
				}
			}
			if(strcmp(word, ".wfill") == 0){
				if(ad.left == false){
					//ERROR
					addERROR("Trying to add a word on the right side of memory map", line);
				}
				else{
					string w;
					int v;
					fscanf(source, "%d", &v);
					fscanf(source, " %s", w);
					convertToStringSize10(w, labels);
					for(int i=0; i<v; i++){
						writeWordOnMap(w, ad, map, &printLine, labels);
						ad.ad = ad.ad +1;
					}
				}
			}
		}

		updateAddress(word, &ad, source);
	}

	if(ad.left == false){
		writeMap("00", "000", ad, labels, map, &printLine);
	}

	//Add 1 to the line counter
	if(kill == '\n'){
			line++;
	}

}

/*Convert a number entrance, as an address to the format of the memry map*/
void convertToStringSize10(string s, Head labels){
	int size = strlen(s);

	//Removing ""
	if(s[0] == '\"'){
		for(int i=0; i<size-2; i++){
			s[i] = s[i+1];
		}
		s[size-2] = '\0';
	}

	Node n = findStringList(labels, s);
	//Encontramos um label!
	if(n != NULL){
		//it belongs to the labels
		sprintf (s, "%d", n->value);
	}

	//Hexadecimal
	size = strlen(s);
	if(s[0] == '0' && s[1] == 'x'){
		for(int i=0; i<size-1; i++){
			s[i] = s[i+2];
		}
		return;
	}

	else if(checkIfNumber(s) == false && n == NULL){
		addERROR("Rotulo invalido", 1);
	}

	int quotient = convertNumber(s);
	string hexadecimalNumber;
	int i = 0;

    while(quotient!=0){
        int temp = quotient % 16;

	    //To convert integer into character
	    if( temp < 10)
	        temp = temp + 48;
	    else
	        temp = temp + 'A' - 10;

	    hexadecimalNumber[i++] = temp;
	    quotient = quotient / 16;
    }
    hexadecimalNumber[i] = 0;

	//decimal
	strcpy(s, "0000000000");
	size = strlen(hexadecimalNumber);
	for(i = 0; i< size; i++){
		s[9-i] = hexadecimalNumber[i];
	}
}

/*Convert a number entrance, as an address to the format of the memry map*/
void convertToStringSize3(string s, Head labels){
	int size = strlen(s);

	//Removing ""
	for(int i=0; i<size-2; i++){
		s[i] = s[i+1];
	}
	s[size-2] = '\0';

	Node n = findStringList(labels, s);
	//Encontramos um label!
	if(n != NULL){
		//it belongs to the labels
		sprintf (s, "%d", n->value);
	}

	//Hexadecimal
	if(s[0] == '0' && s[1] == 'x'){
		size = strlen(s);
		s[0] = s[size-3];
		s[1] = s[size-2];
		s[2] = s[size-1];
		s[3] = 0;
		return;
	}

	else if(checkIfNumber(s) == false && n == NULL){
		addERROR("Rotulo invalido", 1);
	}

	int quotient = convertNumber(s);
	string hexadecimalNumber;
	int i = 0;

    while(quotient!=0){
        int temp = quotient % 16;

	    //To convert integer into character
	    if( temp < 10)
	        temp = temp + 48;
	    else
	        temp = temp + 'A' - 10;

	    hexadecimalNumber[i++] = temp;
	    quotient = quotient / 16;
    }
    hexadecimalNumber[i] = 0;

	//decimal
	strcpy(s, "000");
	size = strlen(hexadecimalNumber);
	for(i = 0; i< size; i++){
		s[2-i] = hexadecimalNumber[i];
	}
}

void writeMap(string op, string add, address ad, Head labels, string *map, int *printLine){

	if(ad.left == true){

		//There was a address change befor this command
		if(strlen(map[*printLine]) != 0){
			strcat(map[*printLine], " 00 000");
			*printLine = *printLine + 1;
		}
		string k;
		sprintf (k, "\"%d\"", ad.ad);
		convertToStringSize3(k, labels);
		strcat(map[*printLine], k);
		strcat(map[*printLine], " ");
		strcat(map[*printLine], op);
		strcat(map[*printLine], " ");
		strcat(map[*printLine], add);
		return;
	}

	else if(ad.left == false){
		strcat(map[*printLine], " ");
		strcat(map[*printLine], op);
		strcat(map[*printLine], " ");
		strcat(map[*printLine], add);
		*printLine = *printLine + 1;
	}

}

void writeWordOnMap(string word, address ad, string *map, int *printLine, Head labels){

	//Adding right position on the map
	string k;
	sprintf (k, "\"%d\"", ad.ad);
	convertToStringSize3(k, labels);
	strcat(map[*printLine], k);
	strcat(map[*printLine], " ");

	int size = strlen(map[*printLine]);
	for(int i=0, j=0; i<= 10; i++, j++){
		map[*printLine][size + j] = word[i];
		if(j == 1 || j == 5 || j == 8){
			map[*printLine][size + j + 1] = 0;
			strcat(map[*printLine], " ");
			j++;
		}
	}
	*printLine = *printLine + 1;
}

/*Check if the parameter string is a valid Directive*/
bool checkDirective(string s){

	if(s[0] != '.'){
		return false;
	}
	return true;
}

/*Check if a given string is made only of number characters*/
bool checkIfNumber(string s){
	int size = strlen(s);

	for(int i=0; i<size; i++){
		if(!(s[i] >= '0' && s[i] <= '9'))
			return false;
	}
	return true;
}

void updateAddress(string s, address *ad, FILE *source){

	//Checking for directives wich may change the position
	if(s[0] == '.'){
		if (strcmp(s, ".org") == 0){
			string orgSize;
			fscanf(source, " %s", orgSize);
			(*ad).ad = convertNumber(orgSize);
			(*ad).left = 1;
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
