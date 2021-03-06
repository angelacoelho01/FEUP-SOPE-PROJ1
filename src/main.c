#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "permissions/xmod.h"

#define MAX_STR_LEN 256

int main(int arg, char *argv[], char *envp[]){
	if((arg < 3) || (arg > 4)){
		printf("usage: ./xmod [OPTIONS] MODE FILE/DIR\n");
		exit(1);
	}

	char mode[MAX_STR_LEN], pathname[MAX_STR_LEN];

	if(arg == 3){ // If no options
		strncpy(mode, argv[1], strlen(argv[1]) + 1);
		strncpy(pathname, argv[2], strlen(argv[2]) + 1);
		
		xmod(NULL, mode, pathname);
	}
	else if(arg == 4){
		char options[MAX_STR_LEN];

		strncpy(options, argv[1], strlen(argv[1]) + 1);
		strncpy(mode, argv[2], strlen(argv[2]) + 1);
		strncpy(pathname, argv[3], strlen(argv[3]) + 1);

		xmod(options, mode, pathname);
	}

	exit(0);
}