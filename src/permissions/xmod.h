#ifndef XMOD_H_
#define XMOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_STR_LEN 256

int xmod(const char* options, const char* mode, const char* pathname);

mode_t handlePermissions(const char* options, const char* mode, const char* pathname);

mode_t addPermissions(struct stat st, const char user, const int read, const int write, const int execute);

mode_t removePermissions(struct stat st, const char user, const int read, const int write, const int execute);

#endif /* XMOD_H_ */

