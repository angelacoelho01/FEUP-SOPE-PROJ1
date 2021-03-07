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
		exit(USAGE_WRONG);
	}

	char* mode = argv[argc - 2];
	char* pathname = argv[argc - 1];
	char* options = argc == 3? NULL : argv[1];
	int opt_v = 0, opt_c = 0, opt_R = 0;

	if(options != NULL){

		if(options[0] != '-'){ usageNotRight(); exit(USAGE_WRONG);}

		opt_v = strchr(options, 'v') == NULL ? 0 : 1;
		opt_c = strchr(options, 'c') == NULL? 0 : 1;
		opt_R = strchr(options, 'R') == NULL? 0 : 1;

		int active = 0; 
		if(opt_v) active++;
		if(opt_c) active++;
		if(opt_R) active++; 

		if(strlen(options) > active+1){ usageNotRight(); exit(USAGE_WRONG);}
	}

	printf(" v: %d, c: %d, R: %d\n", opt_v, opt_c, opt_R);
	//check if octal mode

	if (isPathDir(pathname)){
		// the value of this bool represents if -R option exists
		//bool change_subdirectories = true;
		
		printf("It's a directory!\n"); // to test purposes
		// with -R option we need to recursevely change the permissions 
		// of every file/dir within the directory, and other subdirectories that may exist

		if (iterateDirectory(options, mode, pathname, opt_R) != 0) {
			fprintf(stderr, "Error changing dir's files permissions\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		printf("It's a regular file!\n"); // to test purposes
		if (xmod(options, mode, pathname) != 0) {
			fprintf(stderr, "Error changing file's permissions\n");
			exit(EXIT_FAILURE);
		}
	}
	
	return 0;
}
