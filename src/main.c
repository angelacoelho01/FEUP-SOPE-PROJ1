#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>

bool is_pathname_dir(const char *pathname) {
	// try to open
	FILE *f = fopen(pathname, "r");
	if (f == NULL) {
		fprintf(stderr, "\nError in opening File %s", pathname);
		exit(EXIT_FAILURE);
	}
	
	// see if the root is a file or a directory
	bool is_dir = false;
	struct stat sb;
	if (stat(pathname, &sb) == -1) {
		fprintf(stderr, "\nError in getting File %s status", pathname);
		exit(EXIT_FAILURE);
	}
	
	// the path represent a dir
	if (sb.st_mode == S_IFDIR) 
		is_dir = true;
		
	// close
	if (fclose(f) == -1) {
		fprintf(stderr, "\nError in closing File %s", pathname);
		exit(EXIT_FAILURE);
	}
	
	return is_dir;
}

int change_file_permissions(const char *filename) {
	// the act of be able to change permissions is done by writing the filenames that we acess
	printf("\n %s", filename);
	
	return 0;
}

int change_dir_files_permissions(const char *dirname, bool iterate_sub_dirs) {
	// if is a dir -> run throw the dir
	//     -> if in any point we find another dir -> create a new process that will run throw 
	//   this dir too (if option -R)
	
	// open directory
	DIR *dir = opendir(dirname);
	if (dir == NULL) {
		fprintf(stderr, "\nError in opening dir %s", dirname);
		return -1;
	}
	
	// read the content in the directory
	struct dirent *dir_content;
	int status; 
	
	while ((dir_content = readdir(dir)) != NULL) {
		// its a directory and option -R is set true
		if ((is_pathname_dir(dir_content->d_name)) && (iterate_sub_dirs)) {
			// create a new process - the child - who will iterate over this subdirectory
			pid_t pid = fork();
			if (pid == -1) {
				fprintf(stderr, "\nError in creating a new process");
				break; // --> do to return with -1 <--
			}
			else if (pid == 0) { // child process
				change_dir_files_permissions(dir_content->d_name, iterate_sub_dirs);
				// --> make this to pass the directory name by changing the last line arguments <--
			} else {
				// parent wait for the child to end 
				waitpid(pid, &status, 0);
			}
		} else {
			// its a file in the directory
			change_file_permissions(dir_content->d_name);
		}
	}
	
	// close directory
	if (closedir(dir) == -1) {
		fprintf(stderr, "\nError in closing dir %s", dirname);
		return -1;
	}
	
	return 0;
}

int main(int numArg, char *argv[], char *env[]){
       // assumindo a correcao das variaveis da linha de comandos
	// xpm [OPTIONS] (MODE | OCTAL_MODE) FILE/DIR
	
	char *root = argv[numArg - 1]; // the last parameter identifies the path location
	
	// then the value of this bool depends if -R option exists
	bool change_subdirectories = true;
	
	if (is_pathname_dir(root)) {
		printf("\n Is a directory!");
		// with -R option we need to recursevely change the permissions 
		// of every file within the directory, and other subdirectories that may exist
		if (change_dir_files_permissions(root, change_subdirectories) == -1) {
			fprintf(stderr, "\nError changing dir's files permissions");
			exit(EXIT_FAILURE);
		}
	} else {
		printf("\n Is a regular file!");
		if (change_file_permissions(root) == -1) {
			fprintf(stderr, "\nError changing File %s permissions", root);
			exit(EXIT_FAILURE);
		}
	}
	
	printf("\nThanks for usinf the program!\n");

	return 0;
}
