#include "filesystem.h"


bool isPathDir(const char *path) {
	// try to open
	FILE *f = fopen(path, "r");
	if (f == NULL) {
		fprintf(stderr, "Error in opening %s\n", path);
		exit(EXIT_FAILURE);
	}
	// see if the root is a file or a directory
	bool is_dir = false;
	struct stat sb;
	if (stat(path, &sb) == -1) {
		fprintf(stderr, "Error in getting %s status\n", path);
		exit(EXIT_FAILURE);
	}
	
	// the path represent a dir
	if (S_ISDIR(sb.st_mode)) 
		is_dir = true;
		
	// close
	if (fclose(f) == -1) {
		fprintf(stderr, "Error in closing %s\n", path);
		exit(EXIT_FAILURE);
	}
	
	return is_dir;
}

int iterateDirectory(const char *options, const char *mode, const char *dirpath) {
	int error = 0;
	
	// change dir's permissions
	if (xmod(options, mode, dirpath) != 0) {
		fprintf(stderr, "Error changing dir's permissions: %s\n", dirpath);
		return -1;
	}
	
	// open directory
	DIR *d; 
	if ((d = opendir(dirpath)) == NULL) {
		fprintf(stderr, "Error in opening dir %s\n", dirpath);
		return -1;
	}
	
	// read the content in the directory
	struct dirent *dir;
	int status; 
	
	while ((dir = readdir(d)) != NULL) {
		// (ignore '.' and '..' directories)
		if ((strcmp(dir->d_name, ".")) == 0 || (strcmp(dir->d_name, "..") == 0)) {
			continue;
		}
		
		// build the path from the directory
		char path[MAX_STR_LEN] = "";
		strcat(strcat(strcat(path, dirpath), "/"), dir->d_name);
		
		// its a directory  
		if (isPathDir(path)) {
						
			// create a new process - the child - who will iterate over this subdirectory
			pid_t pid = fork();
			if (pid == -1) {
				fprintf(stderr, "Error in creating a new process\n");
				error = -1;
				break;
			} else if (pid == 0) { // child process
				writeToLogger(getpid(), PROC_CREAT, "args");
				return (iterateDirectory(options, mode, path));
			} else {
				// parent wait for the child to end 
				waitpid(pid, &status, 0);
				char exit_status[MAX_STR_LEN];
				sprintf(exit_status, "%d", WEXITSTATUS(status));
				printf("EXIT STATUS = %d\n", WEXITSTATUS(status));
				writeToLogger(getpid(), PROC_EXIT, exit_status);
			}
		} else {
			// its a file in the directory
			if (xmod(options, mode, path) != 0) {
				fprintf(stderr, "Error changing file's permissions: %s\n", path);
				error = -1;
				break;
			}
		}

	}
	
	// close directory
	if (closedir(d) == -1) {
		fprintf(stderr, "Error in closing dir %s\n", dirpath);
		return -1;
	}
	
	return error;
}
