#include "logger.h"

#include "utils.h"	

int LOGGER_FD;
struct timespec START_TIME;
char *line_args;

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