#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "permissions/xmod.h"
#include "filesystem/filesystem.h"

#define MAX_STR_LEN 256

int main(int argc, char *argv[], char *envp[]){
	if ((argc < 3) || (argc > 4)){
		printf("usage: ./xmod [OPTIONS] MODE FILE/DIR\n");
		exit(1);
	}

	char* mode = argv[argc - 2];
	char* pathname = argv[argc - 1];
	char* options = argc == 3? NULL : argv[1];

	if (isPathDir(pathname) && strstr(options, "R") != NULL){
		// the value of this bool represents if -R option exists
		//bool change_subdirectories = true;
		
		printf("It's a directory!\n"); // to test purposes
		// with -R option we need to recursevely change the permissions 
		// of every file/dir within the directory, and other subdirectories that may exist

		if (iterateDirectory(options, mode, pathname, true) != 0) {
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
