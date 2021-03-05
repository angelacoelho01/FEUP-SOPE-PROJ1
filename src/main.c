#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "permissions/permissions.h"
#include "filesystem/filesystem.h"

int main(int numArg, char *argv[], char *env[]){
    // assumindo a correcao das variaveis da linha de comandos
	// xpm [OPTIONS] (MODE | OCTAL_MODE) FILE/DIR
	
	char *root = argv[numArg - 1]; // the last parameter identifies the path location
	
	if (is_path_dir(root)) {
		// the value of this bool represents if -R option exists
		//bool change_subdirectories = true;
		
		printf("Is a directory! \n"); // to test purposes
		// with -R option we need to recursevely change the permissions 
		// of every file/dir within the directory, and other subdirectories that may exist
		if (iterate_directory(root, true) == -1) {
			fprintf(stderr, "Error changing dir's files permissions \n");
			exit(EXIT_FAILURE);
		}
	} else {
		printf("Is a regular file! \n "); // to test purposes
		if (change_permissions(root) == -1) {
			fprintf(stderr, "Error changing File %s permissions \n", root);
			exit(EXIT_FAILURE);
		}
	}
	
	// all the possible processes that may exit by iterating each one a respective 
	// subdirectory will continue here
	// next print would be done by all the proccesses that the program created
	// printf("A process ended\n");

	return 0;
}
