#ifndef XMOD_H_
#define XMOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_STR_LEN 256

int xmod(char* options, char* mode, char* pathname);

mode_t add_permission(char user, char operator, char* permissions, char* pathname);

#endif /* XMOD_H_ */

