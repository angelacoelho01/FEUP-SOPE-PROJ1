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
    char* str_mode = (char*)malloc(MAX_STR_LEN);
    memset(str_mode, 0, MAX_STR_LEN);

	for(int i = 0; i < n; i++){
		if(mode & read[i]) strcat(str_mode, "r");
		else strcat(str_mode, "-");

		if(mode & write[i]) strcat(str_mode, "w");
		else strcat(str_mode, "-");

		if(mode & execute[i]) strcat(str_mode, "x");
		else strcat(str_mode, "-");
	}

    return str_mode;
}