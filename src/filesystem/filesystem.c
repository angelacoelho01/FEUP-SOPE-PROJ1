#include "filesystem.h"

bool isPathDir(const char *path) {
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

int iterateDirectory(const char* options, const char* mode, const char *dirpath, bool iterate_sub_dirs) {
	// --> before or after open te dir ?? <--
	xmod(options, mode, dirpath);
	
	// option -R is set true 
	if (iterate_sub_dirs) {
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
			
			// build the path from the directory (--> change to not depend of the lenght <--)
			char path[80] = ""; char separator = '/';
			strcat(strcat(strcat(path, dirpath), &separator), dir->d_name);
			
			// its a directory  
			if (isPathDir(path)) {
							
				// create a new process - the child - who will iterate over this subdirectory
				pid_t pid = fork();
				if (pid == -1) {
					fprintf(stderr, "Error in creating a new process\n");
					break; // --> do to return with -1 <--
				}
				else if (pid == 0) { // child process
					return (iterateDirectory(options, mode, path, iterate_sub_dirs));
					// --> make this to pass the directory name by changing the last line arguments <--
				} else {
					// parent wait for the child to end 
					waitpid(pid, &status, 0);
				}
			} else {
				// its a file in the directory
				xmod(options, mode, path);
			}
		}
		
		// close directory
		if (closedir(d) == -1) {
			fprintf(stderr, "Error in closing dir %s \n", dirpath);
			return -1;
		}
	}
	
	return 0;
}
