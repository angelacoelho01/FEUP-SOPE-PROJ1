#include "logger.h"

#include "utils.h"	

int LOGGER_FD;
struct timespec START_TIME;
char line_args[MAX_STR_LEN];
mode_t new_perm, old_perm;

int openLogger() {
    // Get logger path
    char *path = getenv("LOG_FILENAME");

    if(path == NULL) return 0;

    LOGGER_FD = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0777);

    return 1;
}

int writeToLogger(int pid, const char *event, const char *info) {
    char reg[256];
    sprintf(reg, "%f ; %d ; %s ; %s\n", getElapsedTime(START_TIME), pid, event, info);
    write(LOGGER_FD, reg, strlen(reg));
    return 0;
}

int closeLogger() {
    return close(LOGGER_FD);
}

int getInfoSig(char *info, const char *signal, int pid){
    sprintf(info, "%s : %d", signal, pid);
    return 0;
}

char* getInfoFModf(const char *fname) {
    char *info = (char*)malloc(MAX_STR_LEN);
    sprintf(info, "%s : 0%o : 0%o", fname, old_perm, new_perm);
    return info;
}

int getOldPerm() {
    return 0;
}

int getNewPerm() {
    return 0;
}
