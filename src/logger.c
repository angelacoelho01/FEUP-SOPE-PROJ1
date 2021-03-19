#include "logger.h"
#include "utils.h"	

int LOGGER_FD;
struct timespec START_TIME;
long start_time;
char line_args[MAX_STR_LEN];
mode_t new_perm, old_perm;
int env_def = 0;

int openLogger() {
    // Get logger path
    char *path = getenv("LOG_FILENAME");

    if(path == NULL) return 0;

    if((LOGGER_FD = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0777)) == -1) {
        perror("open()");
        return -1;
    }

    return LOGGER_FD;
}

int writeToLogger(int pid, const char *event, const char *info) {
    if(!env_def) return 0;

    char reg[256];
    sprintf(reg, "%f ; %d ; %s ; %s\n", getElapsedTime(START_TIME), pid, event, info);

    int no_bytes = write(LOGGER_FD, reg, strlen(reg));

    if(no_bytes == -1) {
        perror("write()");
        return -1;
    }

    return no_bytes;
}

int closeLogger() {
    int ret_value = close(LOGGER_FD);

    if(ret_value == -1) {
        perror("close()");
        return -1;
    }

    return ret_value;
}

char* getInfoSig(const char *signal, const pid_t pid) {
    char *info = (char*)malloc(MAX_STR_LEN);
    sprintf(info, "%s : %d", signal, pid);
    return info;
}

char* getGroupInfoSig(const char *signal, pid_t gid) {
    char *info = (char*)malloc(MAX_STR_LEN);
    sprintf(info, "%s : (%d)", signal, gid);
    return info;
}

char* getInfoFModf(const char *path) {
    char *info = (char*)malloc(MAX_STR_LEN);
    sprintf(info, "%s : 0%o : 0%o", path, old_perm, new_perm);
    return info;
}
