#include <stdio.h>
#include <stdlib.h>

int main(int numArg, char *argv[], char *env[]){

	printf("Print all the arguments\n");

	for (int i = 0; i < numArg; i++){
		printf(" %d - %s\n", i, argv[i]);
	}
       	
	exit(0);
}
