#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "permissions/xmod.h"
#include "filesystem/filesystem.h"

#define MAX_STR_LEN 256

int main(int arg, char *argv[], char *envp[]){
	if((arg < 3) || (arg > 4)){
		printf("usage: ./xmod [OPTIONS] MODE FILE/DIR\n");
		exit(1);
	}

	char* mode = argv[arg - 2];
	char* pathname = argv[arg - 1];
	char* options = arg == 3? NULL : argv[1];

	if(isPathDir(pathname)){
		// the value of this bool represents if -R option exists
		//bool change_subdirectories = true;
		
		printf("It's a directory!\n"); // to test purposes
		// with -R option we need to recursevely change the permissions 
		// of every file/dir within the directory, and other subdirectories that may exist

		if (iterateDirectory(options, mode, pathname, true) == -1) {
			fprintf(stderr, "Error changing dir's files permissions\n");
			exit(EXIT_FAILURE);
		}
	}
	else{
		printf("It's a regular file!\n"); // to test purposes
		xmod(options, mode, pathname);
	}
	
	exit(0);
}
