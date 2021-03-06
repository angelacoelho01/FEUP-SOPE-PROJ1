#include "xmod.h"

int xmod(const char* options, const char* mode, const char* pathname){
	mode_t mode_mask = handlePermissions(options, mode, pathname);

	if(chmod(pathname, mode_mask) == -1){
		perror("chmod()");
		exit(1);
	}

	exit(0);
}

mode_t handlePermissions(const char* options, const char* mode, const char* pathname){
	char user, operator;
	char permissions[MAX_STR_LEN];
    mode_t mode_mask;
	struct stat st;
	int read, write, execute;

	strcpy(&user, &mode[0]);
	strcpy(&operator, &mode[1]);
	strcpy(permissions, &mode[2]);

	read = strchr(permissions, 'r') == NULL ? 0 : 1;
	write = strchr(permissions, 'w') == NULL? 0 : 1;
	execute = strchr(permissions, 'x') == NULL? 0 : 1;

	if(stat(pathname, &st) == -1){
		perror("stat()");
		exit(1);
	}
	
    if(operator == '+') mode_mask = addPermissions(st, user, read, write, execute);
    else{
        printf("Under construction.\n");
        exit(2);
    }

	return mode_mask;
}

mode_t addPermissions(struct stat st, const char user, const int read, const int write, const int execute){
	int all = user == 'a' ? 1 : 0;

	if(read){
		if(user == 'o' || all) st.st_mode |= S_IROTH;
		if(user == 'g' || all) st.st_mode |= S_IRGRP;
		if(user == 'u' || all) st.st_mode |= S_IRUSR;
	}

	if(write){
		if(user == 'o' || all) st.st_mode |= S_IWOTH;
		if(user == 'g' || all) st.st_mode |= S_IWGRP;
		if(user == 'u' || all) st.st_mode |= S_IWUSR;
	}

	if(execute){
		if(user == 'o' || all) st.st_mode |= S_IXOTH;
		if(user == 'g' || all) st.st_mode |= S_IXGRP;
		if(user == 'u' || all) st.st_mode |= S_IXUSR;
	}

	return st.st_mode;
}
