#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/ssl.h>
#include <openssl/sha.h>
#include "BlockChain_Tools.c"



int main(int argc, char argv[]){
	BlockChain l;
	l.start = NULL;
	l.len = 0;
	int operation;
	while (true){
		printf("Which operation do you need?\n0)Quit\n1)Add\n2)Delete\n3)Check Hash\n4)Print\nPrint number of operation: ");
		scanf("%d", &operation);
		if (operation == 0){
			Quit(&l);
			break;
		}
		else if (operation == 1){
			Add(&l);
		}
		else if (operation == 2){
			Delete(&l);
		}
		else if (operation == 3){
			CheckHash(&l);
		}
		else if (operation == 4){
			Print(&l);
		}
		else{
			printf("Incorrect operation!!!\n");
		}
	}
	return 0;
}
