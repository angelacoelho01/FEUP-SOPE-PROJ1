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
	if ((argc < 3) || (argc > 6)){
		usageNotRight();
		exit(USAGE_WRONG);
	}

	char* mode = argv[argc - 2];
	char* pathname = argv[argc - 1];
	char* options = argc == 3? NULL : argv[1];
	int opt_v = 0, opt_c = 0, opt_R = 0;

	for(int i = 1; i <= argc-3; i++){
		options = argv[i];

		if(strlen(argv[i]) > 2){ usageNotRight(); exit(USAGE_WRONG);}

		//check in argv[i] the options not found yet
		if(!opt_v){
			if(strstr(options, "-v") != NULL){
				opt_v = 1; continue;
			}
		}
		if(!opt_c){
			if(strstr(options, "-c") != NULL){
				opt_c = 1; continue;
			}
		}
		if(!opt_R){
			if(strstr(options, "-R") != NULL){
				opt_R = 1; continue;
			}
		}
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
