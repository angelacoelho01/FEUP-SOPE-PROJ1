#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_STR_LEN 256

char* getFileName(const char* path_name);

char* convertPermsToString(const mode_t perms);

int isNumber(const char *str);

int findChar(const char possible_str[], unsigned n, const char ch);

void flush_in(void);

#endif /* UTILS_H_ */
