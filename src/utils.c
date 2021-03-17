#include "utils.h"

#include <ctype.h>

char *getFileName(const char *path_name) {
    char *path = (char*)malloc(MAX_STR_LEN);
    strcpy(path, path_name);

    // In case path_name is already the file_name returns just path
    return strchr(path_name, '/') == NULL ? path : basename(path);
}

char *convertPermsToString(const mode_t perms){
    const int n = 3;
    const int read[] = {S_IRUSR, S_IRGRP, S_IROTH};
    const int write[] = {S_IWUSR, S_IWGRP, S_IWOTH};
    const int execute[] = {S_IXUSR, S_IXGRP, S_IXOTH};
    char *str_perms = (char*)malloc(MAX_STR_LEN);
    memset(str_perms, 0, MAX_STR_LEN);

    for(int i = 0; i < n; i++){
        if(perms & read[i]) strcat(str_perms, "r");
        else strcat(str_perms, "-");

        if(perms & write[i]) strcat(str_perms, "w");
        else strcat(str_perms, "-");

        if(perms & execute[i]) strcat(str_perms, "x");
        else strcat(str_perms, "-");
    }

    return str_perms;
}

int isNumber(const char *str){
    for(int i = 0; str[i] != 0; i++){
        if(!isdigit(str[i])) return 0;
    }
    return 1;
}

int findChar(const char possible_str[], unsigned n, const char ch){
    for(unsigned i = 0; i < n; i++){
        if(ch == possible_str[i]) return 1;
    }
    return 0;
}

mode_t resetModeUser(const mode_t current_mode, const char user){
    if(user == 'u') return current_mode & RESET_MODE_USR;
    else if(user == 'g') return current_mode & RESET_MODE_GRP;
    else if(user == 'o') return current_mode & RESET_MODE_OTH;
    return current_mode & RESET_MODE_ALL;
}

char readAnswer(){ 
    char c;

    // Wait for valid input
    while(1) {
        scanf(" %c", &c);
        if (c != 'y' && c != 'n')
            printf("Invalid Answer! (y/n)? ");
        else 
            return c;
    } 
}
