#include "filesystem.h"

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

int iterate_directory(const char *dirpath, bool iterate_sub_dirs) {
	// --> before or after open te dir ?? <--
	change_permissions(dirpath);
	
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
			//strcat(strncat(strcat(path, dirpath), &separator, 1), dir->d_name);
			strncat(path, dirpath, strlen(dirpath) + 1);
			strncat(path, &separator, 1);
			strncat(path, dir->d_name, strlen(dir->d_name) + 1);
			
			// its a directory  
			if (is_path_dir(path)) {
							
				// create a new process - the child - who will iterate over this subdirectory
				pid_t pid = fork();
				if (pid == -1) {
					fprintf(stderr, "Error in creating a new process\n");
					break; // --> do to return with -1 <--
				}
				else if (pid == 0) { // child process
					return (iterate_directory(path, iterate_sub_dirs));
					// --> make this to pass the directory name by changing the last line arguments <--
				} else {
					// parent wait for the child to end 
					waitpid(pid, &status, 0);
				}
			} else {
				// its a file in the directory
				change_permissions(path);
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
