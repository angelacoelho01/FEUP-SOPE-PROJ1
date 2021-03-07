#include "utils.h"

char* getFileName(const char* path_name){
    char* path = (char*)malloc(MAX_STR_LEN);
    strcpy(path, path_name);

    // In case path_name is already the file_name returns just path
    return strchr(path_name, '/') == NULL ? path : basename(path);
}

char* convertModeToString(const mode_t mode){
	const int n = 3;
	const int read[] = {S_IRUSR, S_IRGRP, S_IROTH};
	const int write[] = {S_IWUSR, S_IWGRP, S_IWOTH};
	const int execute[] = {S_IXUSR, S_IXGRP, S_IXOTH};
    char* perm = (char*)malloc(MAX_STR_LEN);

	for(int i = 0; i < n; i++){
		if(mode & read[i]) strcat(perm, "r");
		else strcat(perm, "-");

		if(mode & write[i]) strcat(perm, "w");
		else strcat(perm, "-");

		if(mode & execute[i]) strcat(perm, "x");
		else strcat(perm, "-");
	}

    return perm;
}