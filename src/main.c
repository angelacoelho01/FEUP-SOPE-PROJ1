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

int change_permissions(const char *path) {
	// the act of be able to change permissions is done by writing the filenames that we acess
	printf(" %s \n", path);
	
	return 0;
}

int change_dir_permissions(const char *dirpath, bool iterate_sub_dirs) {
	// if is a dir -> run throw the dir
	//     -> if in any point we find another dir -> create a new process that will run throw 
	//   this dir too (if option -R)
	
	// --> before or after open te dir ?? <--
	change_permissions(dirpath);
	
	if (iterate_sub_dirs) {
		// open directory
		DIR *d; 
		if ((d = opendir(dirpath)) == NULL) {
			fprintf(stderr, "Error in opening dir %s\n", dirpath);
			return -1;
		}
		// printf("DIR OPEN! \n"); // to test purposes
		
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
			strcat(strncat(strcat(path, dirpath), &separator, 1), dir->d_name); 	
			// printf("PATH : %s\n", path); // to test purposes
			
			//its a directory and option -R is set true 
			if (is_path_dir(path)) {
				// printf("IT'S A DIR AND IS TO ITERATE! \n"); // to test purposes
					
				// create a new process - the child - who will iterate over this subdirectory
				pid_t pid = fork();
				if (pid == -1) {
					fprintf(stderr, "Error in creating a new process\n");
					break; // --> do to return with -1 <--
				}
				else if (pid == 0) { // child process
					return (change_dir_permissions(path, iterate_sub_dirs));
					// --> make this to pass the directory name by changing the last line arguments <--
				} else {
					// parent wait for the child to end 
					waitpid(pid, &status, 0);
				}
			} else {
				// printf("IT'S A FILE! \n"); // to test purposes
				// its a file in the directory
				change_permissions(path);
			}
		}
		
		// close directory
		if (closedir(d) == -1) {
			fprintf(stderr, "Error in closing dir %s \n", dirpath);
			return -1;
		}
		
		// printf("DIR CLOSED! \n"); // to test purposes
	}
	
	return 0;
}

int main(int numArg, char *argv[], char *env[]){
       // assumindo a correcao das variaveis da linha de comandos
	// xpm [OPTIONS] (MODE | OCTAL_MODE) FILE/DIR
	
	char *root = argv[numArg - 1]; // the last parameter identifies the path location
	
	// then the value of this bool depends if -R option exists
	bool change_subdirectories = true;
	
	if (is_path_dir(root)) {
		printf("Is a directory! \n"); // to test purposes
		// with -R option we need to recursevely change the permissions 
		// of every file/dir within the directory, and other subdirectories that may exist
		if (change_dir_permissions(root, change_subdirectories) == -1) {
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
	// printf("\nThanks for using the program!\n");

	return 0;
}
