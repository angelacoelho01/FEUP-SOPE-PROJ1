#include "xmod.h"

int xmod(const char* options, const char* mode, const char* pathname){
	printf("paht = %s\n", pathname);
	mode_t mode_mask = changePermissions(options, mode, pathname);

	if(chmod(pathname, mode_mask) == -1){
		perror("chmod()");
		exit(1);
	}

	return 0;
}

mode_t changePermissions(const char* options, const char* mode, const char* pathname){
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
	int all = user == 'a' ? 1 : 0;

	if(operator == '=') st.st_mode &= RESET_PERM;

	if(read){
		if(user == 'o' || all) st.st_mode = remove ? st.st_mode & ~S_IROTH : st.st_mode | S_IROTH;
		if(user == 'g' || all) st.st_mode = remove ? st.st_mode & ~S_IRGRP : st.st_mode | S_IRGRP;
		if(user == 'u' || all) st.st_mode = remove ? st.st_mode & ~S_IRUSR : st.st_mode | S_IRUSR;
	}

	if(write){
		if(user == 'o' || all) st.st_mode = remove ? st.st_mode & ~S_IWOTH : st.st_mode | S_IWOTH;
		if(user == 'g' || all) st.st_mode = remove ? st.st_mode & ~S_IWGRP : st.st_mode | S_IWGRP;
		if(user == 'u' || all) st.st_mode = remove ? st.st_mode & ~S_IWUSR : st.st_mode | S_IWUSR;
	}

	if(execute){
		if(user == 'o' || all) st.st_mode = remove ? st.st_mode & ~S_IXOTH : st.st_mode | S_IXOTH;
		if(user == 'g' || all) st.st_mode = remove ? st.st_mode & ~S_IXGRP : st.st_mode | S_IXGRP;
		if(user == 'u' || all) st.st_mode = remove ? st.st_mode & ~S_IXUSR : st.st_mode | S_IXUSR;
	}

	return st.st_mode;
}
