#ifndef XMOD_H_
#define XMOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_STR_LEN 256
#define RESET_PERM ~(000777)

int xmod(const char* options, const char* mode, const char* pathname);

mode_t changePermissions(const char* options, const char* mode, const char* pathname);

#endif /* XMOD_H_ */
