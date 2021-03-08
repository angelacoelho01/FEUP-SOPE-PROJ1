#include "xmod.h"

int xmod(const char* options, const char* mode, const char* pathname){
	mode_t mode_mask = handleMode(options, mode, pathname);

	handleOptions(options, pathname, mode_mask);

	if(chmod(pathname, mode_mask) == -1){
		perror("chmod()");
		exit(1);
	}

	return 0;
}

int handleOptions(const char* options, const char* path_name, const mode_t mode_final){
	// In case there wasn't any options passed returns immediately
	if (options == NULL) return 0;

	mode_t mode_init;
	struct stat st;

	if(stat(path_name, &st) == -1){
		perror("stat()");
		exit(1);
	}

	mode_init = st.st_mode;

	int isChange = mode_init == mode_final? 0 : 1;
	int verbose = strchr(options, 'v') == NULL ? 0 : 1;
	int changes = strchr(options, 'c') == NULL ? 0 : 1;
	//const char* file_name = strchr(options, 'R') == NULL? getFileName(path_name) : path_name;
	//int recursive = strchr(options, 'R') == NULL ? 0 : 1;
	char* str_mode_init = convertModeToString(mode_init);
	
	if(isChange && (verbose || changes)){
		char* str_mode_final = convertModeToString(mode_final);
		printf("mode of '%s' changed from 0%o (%s) to 0%o (%s)\n", path_name, (mode_init & GET_MODE), str_mode_init, (mode_final & GET_MODE), str_mode_final);
		
	}
	else if(!isChange && verbose)
		printf("mode of '%s' retained as 0%o (%s)\n", path_name, (mode_final & GET_MODE), str_mode_init);

	return 0;
}

mode_t handleMode(const char* options, const char* mode, const char* pathname){
	char user, operator;
	char Mode[MAX_STR_LEN];
	int read, write, execute;
	struct stat st;

	if(stat(pathname, &st) == -1){
		perror("stat()");
		exit(1);
	}

	strcpy(&user, &mode[0]);
	strcpy(&operator, &mode[1]);
	strcpy(mode, &mode[2]);

	int remove = operator == '-' ? 1 : 0;
	if(operator == '=') st.st_mode &= RESET_MODE;

	read = strchr(mode, 'r') == NULL ? 0 : 1;
	write = strchr(mode, 'w') == NULL? 0 : 1;
	execute = strchr(mode, 'x') == NULL? 0 : 1;


	return getNewMode(st.st_mode, read, write, execute, remove, user);
}

mode_t getNewMode(mode_t mode, const int read, const int write, const int execute, const int remove, const char user){
	int all = user == 'a' ? 1 : 0;

	if(read){
		if(user == 'o' || all) mode = remove ? mode & ~S_IROTH : mode | S_IROTH;
		if(user == 'g' || all) mode = remove ? mode & ~S_IRGRP : mode | S_IRGRP;
		if(user == 'u' || all) mode = remove ? mode & ~S_IRUSR : mode | S_IRUSR;
	}

	if(write){
		if(user == 'o' || all) mode = remove ? mode & ~S_IWOTH : mode | S_IWOTH;
		if(user == 'g' || all) mode = remove ? mode & ~S_IWGRP : mode | S_IWGRP;
		if(user == 'u' || all) mode = remove ? mode & ~S_IWUSR : mode | S_IWUSR;
	}

	if(execute){
		if(user == 'o' || all) mode = remove ? mode & ~S_IXOTH : mode | S_IXOTH;
		if(user == 'g' || all) mode = remove ? mode & ~S_IXGRP : mode | S_IXGRP;
		if(user == 'u' || all) mode = remove ? mode & ~S_IXUSR : mode | S_IXUSR;
	}

	return mode;
}
