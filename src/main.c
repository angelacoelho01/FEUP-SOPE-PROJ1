#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "permissions/xmod.h"
#include "filesystem/filesystem.h"
#include "inputcheck/inputcheck.h"

#define MAX_STR_LEN 256

int main(int argc, char *argv[], char *envp[]){
	if ((argc < 3) || (argc > 4)){
		usageNotRight();
		exit(INPUT_ERROR);
	}

	char* mode = argv[argc - 2];
	char* pathname = argv[argc - 1];
	char* options = argc == 3? NULL : argv[1];
	int opt_v = 0, opt_c = 0, opt_R = 0;

	if(options != NULL){

		if(options[0] != '-'){ usageNotRight(); exit(INPUT_ERROR);}

		opt_v = strchr(options, 'v') == NULL ? 0 : 1;
		opt_c = strchr(options, 'c') == NULL? 0 : 1;
		opt_R = strchr(options, 'R') == NULL? 0 : 1;

		if(!opt_v && !opt_c && !opt_R){ usageNotRight(); exit(INPUT_ERROR);}
	}

	printf(" v: %d, c: %d, R: %d\n", opt_v, opt_c, opt_R);
	//check if octal mode

	if (isPathDir(pathname) && opt_R){	
		printf("It's a directory to iterate!\n"); // to test purposes
		
		if (iterateDirectory(options, mode, pathname) != 0) {
			fprintf(stderr, "Error changing dir's files permissions\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		printf("It's a single file/directory!\n"); // to test purposes
		
		if (xmod(options, mode, pathname) != 0) {
			fprintf(stderr, "Error changing file/directory's permissions\n");
			exit(EXIT_FAILURE);
		}
	}
	
	return 0;
}
