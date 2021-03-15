#include "logger.h"

int LOGGER_FD;

int openLogger() {
    // Get logger path
    char *path = getenv("LOG_FILENAME");

    if(path == NULL) return 0;

    LOGGER_FD = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0777);

    return 0;
}

int writeToLogger(int pid, const char *info) {
    char reg[256];
    sprintf(reg, "instant ; %d ; event ; %s\n", pid, info);
    write(LOGGER_FD, reg, strlen(reg));

    return 0;
}

int closeLogger() {
    return close(LOGGER_FD);
}