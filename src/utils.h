#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MAX_STR_LEN 256
#define RESET_MODE_USR ~(000700)
#define RESET_MODE_GRP ~(000070)
#define RESET_MODE_OTH ~(000007)
#define RESET_MODE_ALL ~(000777)

char* getFileName(const char* path_name);

char* convertPermsToString(const mode_t perms);

int isNumber(const char *str);

int findChar(const char possible_str[], unsigned n, const char ch);

double getElapsedTime(const struct timespec begin);

void getLineArgs(const char *mode, const char *path, const char *options);

char readAnswer(void);

#endif /* UTILS_H_ */
