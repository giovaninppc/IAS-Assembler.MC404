/*Giovani Nascimento Pereira - 168609
 *this part is responsable for creating the memory map
 *by reading it on the FILE and saving on the proper structure*/

#include "memorymap.h"
 #include "reader.h"
#include "text.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void createMemorymap(FILE *source, Head labels, string *map){

	string word;
	//string place = "000 ", op;
	int printLine = 0;
	address ad;
	int line = 0;
	char kill;
	startAddress(&ad);

	while(fscanf(source, " %s", word) != EOF){
		
		fscanf(source, "%c", &kill);
		//printf("debugging :%c\n", kill);
		if(kill == '\n'){
			line++;
		}

		/*Passing Comment*/
		if(word[0] == '#'){
			finishLine(source);
			line++;
			continue;
		}

		else if(checkRegularCommand(word)){
			if(strcmp(word, "LD") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("01", ld, ad, labels, map, &printLine);
			}
			if(strcmp(word, "LD-") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("02", ld, ad, labels, map, &printLine);
			}
			if(strcmp(word, "LD|") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("03", ld, ad, labels, map, &printLine);
			}
			if(strcmp(word, "LDmq") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("0a", ld, ad, labels, map, &printLine);
			}
			if(strcmp(word, "LDmq_mx") == 0){
				string ld;
				fscanf(source, " %s", ld);
				convertToStringSize3(ld, labels);
				writeMap("09", ld, ad, labels, map, &printLine);
			}
		}

		else if(checkDirective(word)){

			if(strcmp(word, ".word") == 0);
		}

		updateAddress(word, &ad, source);

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

		return;
	}

	//Hexadecimal
	if(s[0] == '0' && s[0] == 'x'){
		size = strlen(s);
		s[0] = s[size-3];
		s[1] = s[size-2];
		s[2] = s[size-1];
		s[3] = 0;
		return;
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
	        temp = temp + 'a' - 10;

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
		if(strlen(map[*printLine]) != 0){
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

/*Check if the parameter string is a valid Directive*/
bool checkDirective(string s){

	if(s[0] != '.'){
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
			//printf("%s %d\n", orgSize, (int)strlen(orgSize));
			(*ad).ad = convertNumber(orgSize);
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
