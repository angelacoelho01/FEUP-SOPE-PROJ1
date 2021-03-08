#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include <stdlib.h>


#define MAX_STR_LEN 256

char* getFileName(const char* path_name);

char* convertModeToString(const mode_t mode);

int isNumber(const char* str);

#endif /* UTILS_H_ */
