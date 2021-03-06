#include "xmod.h"

int xmod(const char* options, const char* mode, const char* pathname){
	printf("paht = %s\n", pathname);
	mode_t mode_mask = handlePermissions(options, mode, pathname);

	if(chmod(pathname, mode_mask) == -1){
		perror("chmod()");
		exit(1);
	}

	return 0;
}

mode_t handlePermissions(const char* options, const char* mode, const char* pathname){
	char user, operator;
	char permissions[MAX_STR_LEN];
	int read, write, execute;
	struct stat st;

	if(stat(pathname, &st) == -1){
		perror("stat()");
		exit(1);
	}

	strcpy(&user, &mode[0]);
	strcpy(&operator, &mode[1]);
	strcpy(permissions, &mode[2]);

	read = strchr(permissions, 'r') == NULL ? 0 : 1;
	write = strchr(permissions, 'w') == NULL? 0 : 1;
	execute = strchr(permissions, 'x') == NULL? 0 : 1;

	int remove = operator == '-' ? 1 : 0;

	if(operator == '=') st.st_mode &= RESET_PERM;

	return changePermissions(st.st_mode, read, write, execute, remove, user);
}

mode_t changePermissions(mode_t mode, const int read, const int write, const int execute, const int remove, const char user){
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
