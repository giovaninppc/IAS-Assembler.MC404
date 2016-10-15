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

		removeDots(word);
		/*Passing Comment*/
		if(word[0] == '#'){
			finishLine(source);
			line++;
			continue;
		}

		else if(findStringList(labels, word) != NULL){
			continue;
		}

		else if(checkRegularCommand(word)){

			//LOADs
			if(strcmp(word, "LD") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to LD, missing \"", ld);
				}
				convertToStringSize3(ld, labels);
				writeMap("01", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "LD-") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to LD-, missing \"", ld);
				}
				convertToStringSize3(ld, labels);
				writeMap("02", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "LD|") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to LD|, missing \"", ld);
				}
				convertToStringSize3(ld, labels);
				writeMap("03", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "LDmq") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to LDmq, missing \"", ld);
				}
				convertToStringSize3(ld, labels);
				writeMap("0a", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "LDmq_mx") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to LDmq_mx, missing \"", ld);
				}
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
				string st;
				fscanf(source, " %s", st);

				//Removing "", if possible
				if(removeAspas(st) == false){
					//ERROR
					addERROR("Not a valid reference to STaddr+, missing \"", st);
				}

				//Checking if the reference is an address 
				//(Need to verify left or right)
				Node a = findStringList(labels, st);
				int left;
				if(a != NULL){
					left = a->left;
				}
			
				//Jump left
				if(checkIfNumber(st) == true || checkIfHex(st) 
					|| (a != NULL && left == true)){
					convertToStringSize3(st, labels);
					writeMap("12", st, ad, labels, map, &printLine);
				}
				//Jump right
				else if(a != NULL && left == false){
					convertToStringSize3(st, labels);
					writeMap("13", st, ad, labels, map, &printLine);
				}
			}

			//MATHs
			else if(strcmp(word, "ADD") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to ADD, missing \"", ld);
				}
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
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to ADD|, missing \"", ld);
				}
				convertToStringSize3(ld, labels);
				writeMap("07", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "SUB|") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to SUB|, missing \"", ld);
				}
				convertToStringSize3(ld, labels);
				writeMap("08", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "DIV") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to DIV, missing \"", ld);
				}
				convertToStringSize3(ld, labels);
				writeMap("0C", ld, ad, labels, map, &printLine);
			}
			else if(strcmp(word, "MUL") == 0){
				string ld;
				fscanf(source, " %s", ld);
				if(removeAspas(ld) == false){
					//ERROR
					addERROR("Not a valid reference to MUL, missing \"", ld);
				}
				convertToStringSize3(ld, labels);
				writeMap("0B", ld, ad, labels, map, &printLine);
			}

			//JUMPs
			else if(strcmp(word, "JMP") == 0){
				string jmp;
				fscanf(source, " %s", jmp);

				//Removing "", if possible
				if(removeAspas(jmp) == false){
					//ERROR
					addERROR("Not a valid reference to Jump, missing \"", jmp);
				}

				//Checking if the reference is an address 
				//(Need to verify left or right)
				Node a = findStringList(labels, jmp);
				int left;
				if(a != NULL){
					left = a->left;
				}
			
				//Jump right
				if(a != NULL && left == false){
					convertToStringSize3(jmp, labels);
					writeMap("0E", jmp, ad, labels, map, &printLine);
				}
				//Jump left - always
				else if(checkIfNumber(jmp) || checkIfHex(jmp) || (a!=NULL && left==true)){
					convertToStringSize3(jmp, labels);
					writeMap("0D", jmp, ad, labels, map, &printLine);
				}
			}
			else if(strcmp(word, "JUMP+") == 0){
				string jmp;
				fscanf(source, " %s", jmp);

				//Removing "", if possible
				if(removeAspas(jmp) == false){
					//ERROR
					addERROR("Not a valid reference to Jump+, missing \"", jmp);
				}

				//Checking if the reference is an address 
				//(Need to verify left or right)
				Node a = findStringList(labels, jmp);
				int left;
				if(a != NULL){
					left = a->left;
				}
			
				//Jump left - always
				if(checkIfNumber(jmp) == true || (a != NULL && left == true)){
					convertToStringSize3(jmp, labels);
					writeMap("0F", jmp, ad, labels, map, &printLine);
				}
				else if(a != NULL && left == false){
					convertToStringSize3(jmp, labels);
					writeMap("10", jmp, ad, labels, map, &printLine);
				}
			}	
		}

		else if(checkDirective(word)){
			
			if(strcmp(word, ".word") == 0){
				
				if(ad.left == false){
					//ERROR
					addERROR("Trying to add a word on the right side of memory map", word);
					return;
				}
				else{
					string w;
					fscanf(source, " %s", w);
					removeDots(w);
					convertToStringSize10(w, labels);
					writeWordOnMap(w, ad, map, &printLine, labels);
					ad.ad = ad.ad +1;
				}
			}
			if(strcmp(word, ".wfill") == 0){
				if(ad.left == false){
					//ERROR
					addERROR("Trying to add a word vector on the right side of memory map", 
						word);
					return;
				}
				else{
					string w;
					int v;
					fscanf(source, "%d", &v);
					fscanf(source, " %s", w);
					removeDots(w);
					convertToStringSize10(w, labels);
					for(int i=0; i<v; i++){
						writeWordOnMap(w, ad, map, &printLine, labels);
						ad.ad = ad.ad +1;
					}
				}
			}
		}

		else if(checkIfNumber(word)==false && checkIfHex(word)==false && 
			findStringList(labels,word)==NULL){
			//ERROR
			string e = "Invalid Command ";
			strcat(e, word);
			addERROR(e, word);
			return;
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
	removeAspas(s);

	Node n = findStringList(labels, s);
	//Encontramos um label!
	if(n != NULL){
		//it belongs to the labels
		sprintf (s, "%d", n->value);
	}

	//Hexadecimal
	size = strlen(s);
	if(s[0] == '0' && s[1] == 'x'){
		if(checkIfHex(s) == false){
			addERROR("Invalid Hexadecimal Number", s);
			return;
		}
		for(int i=0; i<size-1; i++){
			s[i] = s[i+2];
		}
		return;
	}

	else if(checkIfNumber(s) == false && n == NULL && checkIfHex(s) == false){
		addERROR("Invalid Label", s);
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
	removeAspas(s);

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
		addERROR("Rotulo invalido", s);
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

/*Check if a given string is a valid Hexadecimal number*/
bool checkIfHex(string s){

	int size = strlen(s);
	if(size != 12 || !(s[0] == '0' && s[1] == 'x')){
		return false;
	}

	for(int i=2; i<size; i++){
		if(!(s[i] >= '0' && s[i] <= '9') && !(s[i] >= 'A' && s[i] <= 'F'))
			return false;
	}
	return true;
}

/*Try to remove the " character, return false if not possible */
bool removeAspas(string s){

	int size = strlen(s);
	if(s[0] == '\"'){
		for(int i=0; i<size-2; i++){
			s[i] = s[i+1];
		}
		s[size-2] = '\0';
	}
	else{
		return false;
	}
	return true;
}

/*Update the address given by parameter (ad) depending on the command s*/
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
