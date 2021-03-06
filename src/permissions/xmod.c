#include "xmod.h"

int xmod(const char* options, const char* mode, const char* pathname){
	char user, operator;
	char permissions[MAX_STR_LEN];
    mode_t mode_mask;

	strcpy(&user, &mode[0]);
	strcpy(&operator, &mode[1]);
	strncpy(permissions, &mode[2], 4);
	
    if(operator == '+') mode_mask = add_permission(user, operator, permissions, pathname);
    else{
        printf("Under construction.\n");
        exit(2);
    }

	if(chmod(pathname, mode_mask) == -1){
		perror("chmod()");
		exit(1);
	}

	exit(0);
}

mode_t add_permission(const char user, const char operator,const char* permissions, const char* pathname){
	struct stat st;

	if(stat(pathname, &st) == -1){
		perror("stat()");
		exit(1);
	}

	char* read = strchr(permissions, 'r');
	char* write = strchr(permissions, 'w');
	char* execute = strchr(permissions, 'x');
	int all = user == 'a' ? 1 : 0;

	if(read != NULL){
		if(user == 'o' || all) st.st_mode |= S_IROTH;
		if(user == 'g' || all) st.st_mode |= S_IRGRP;
		if(user == 'u' || all) st.st_mode |= S_IRUSR;
	}

	if(write != NULL){
		if(user == 'o' || all) st.st_mode |= S_IWOTH;
		if(user == 'g' || all) st.st_mode |= S_IWGRP;
		if(user == 'u' || all) st.st_mode |= S_IWUSR;
	}

	if(execute != NULL){
		if(user == 'o' || all) st.st_mode |= S_IXOTH;
		if(user == 'g' || all) st.st_mode |= S_IXGRP;
		if(user == 'u' || all) st.st_mode |= S_IXUSR;
	}

	return st.st_mode;
}