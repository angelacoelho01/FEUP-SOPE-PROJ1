#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

bool is_path_dir(const char *path) {
	// try to open
	FILE *f = fopen(path, "r");
	if (f == NULL) {
		fprintf(stderr, "Error in opening File %s\n", path);
		exit(EXIT_FAILURE);
	}
	
	// see if the root is a file or a directory
	bool is_dir = false;
	struct stat sb;
	if (stat(path, &sb) == -1) {
		fprintf(stderr, "Error in getting File %s status\n", path);
		exit(EXIT_FAILURE);
	}
	
	// the path represent a dir
	if (S_ISDIR(sb.st_mode)) 
		is_dir = true;
		
	// close
	if (fclose(f) == -1) {
		fprintf(stderr, "Error in closing File %s\n", path);
		exit(EXIT_FAILURE);
	}
	
	return is_dir;
}

int change_file_permissions(const char *filename) {
	// the act of be able to change permissions is done by writing the filenames that we acess
	printf(" %s \n", filename);
	
	return 0;
}

int change_dir_files_permissions(const char *dirname, bool iterate_sub_dirs) {
	// if is a dir -> run throw the dir
	//     -> if in any point we find another dir -> create a new process that will run throw 
	//   this dir too (if option -R)
	
	// open directory
	DIR *d; 
	if ((d = opendir(dirname)) == NULL) {
		fprintf(stderr, "Error in opening dir %s\n", dirname);
		return -1;
	}
	
	printf("DIR OPEN! \n");
	// read the content in the directory
	struct dirent *dir;
	int status; 
	
	while ((dir = readdir(d)) != NULL) {
		// printf("HAS CONTENT! %s \n", dir->d_name); // to test purposes
		
		// (ignore '.' and '..' directories)
		if ((strcmp(dir->d_name, ".")) == 0 || (strcmp(dir->d_name, "..") == 0)) {
			continue;
		}
		
		// build the path from the directory (--> change to not depend of the lenght <--)
		char path[80] = ""; char separator = '/';
		strcat(strncat(strcat(path, dirname), &separator, 1), dir->d_name); 	
		// printf("PATH : %s\n", path);
		
		//its a directory and option -R is set true 
		if ((is_path_dir(path)) && (iterate_sub_dirs)) {
			printf("IT'S A DIR AND IS TO ITERATE! \n");
				
			// create a new process - the child - who will iterate over this subdirectory
			pid_t pid = fork();
			if (pid == -1) {
				fprintf(stderr, "Error in creating a new process\n");
				break; // --> do to return with -1 <--
			}
			else if (pid == 0) { // child process
				change_dir_files_permissions(path, iterate_sub_dirs);
				// --> make this to pass the directory name by changing the last line arguments <--
				return 0;
			} else {
				// parent wait for the child to end 
				waitpid(pid, &status, 0);
			}
		} else {
			printf("IT'S A FILE! \n");
			// its a file in the directory
			change_file_permissions(path);
		}
	}
	
	// close directory
	if (closedir(d) == -1) {
		fprintf(stderr, "Error in closing dir %s \n", dirname);
		return -1;
	}
	
	printf("DIR CLOSED! \n");
	
	return 0;
}

int main(int numArg, char *argv[], char *env[]){
       // assumindo a correcao das variaveis da linha de comandos
	// xpm [OPTIONS] (MODE | OCTAL_MODE) FILE/DIR
	
	char *root = argv[numArg - 1]; // the last parameter identifies the path location
	
	// then the value of this bool depends if -R option exists
	bool change_subdirectories = true;
	
	if (is_path_dir(root)) {
		printf("Is a directory! \n");
		// with -R option we need to recursevely change the permissions 
		// of every file within the directory, and other subdirectories that may exist
		if (change_dir_files_permissions(root, change_subdirectories) == -1) {
			fprintf(stderr, "Error changing dir's files permissions \n");
			exit(EXIT_FAILURE);
		}
	} else {
		printf("Is a regular file! \n ");
		if (change_file_permissions(root) == -1) {
			fprintf(stderr, "Error changing File %s permissions \n", root);
			exit(EXIT_FAILURE);
		}
	}
	
	// all the possible processes that may exit by iterating each one a respective 
	// subdirectory will continue here
	// next print is done by all the proccesses that the program created
	printf("\nThanks for using the program!\n");

	return 0;
}
