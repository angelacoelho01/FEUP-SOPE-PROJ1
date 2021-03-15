#include "logger.h"

#include "utils.h"	

int LOGGER_FD;
struct timespec START_TIME;

int openLogger() {
    // Get logger path
    char *path = getenv("LOG_FILENAME");

    if(path == NULL) return 0;

    LOGGER_FD = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0777);

    return 1;
}

int writeToLogger(int pid, const char *event, const char *info) {
    char reg[256];
    sprintf(reg, "%0.3f ; %d ; %s ; %s\n", getElapsedTime(START_TIME), pid, event, info);
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

int getInfoFModf(char *info, const char *fname, const char* oldPerm, const char* newPerm){
    sprintf(info, "%s : %s : %s", fname, oldPerm, newPerm);
    return 0;
}