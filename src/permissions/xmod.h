#ifndef XMOD_H_
#define XMOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "../utils.h"

#define MAX_STR_LEN 256
#define RESET_MODE ~(000777)
#define GET_MODE 000777

int xmod(const char* options, const char* mode, const char* path_name);

int handleOptions(const char* options, const char* path_name, const mode_t mode_final);

mode_t handleMode(const char* options, const char* mode, const char* path_name);

mode_t getNewMode(mode_t mode, const int read, const int write, const int execute, const int remove, const char user);

mode_t handleModeOctal(const char* options, const char* mode, const char* pathname);

mode_t setOctalMode(mode_t set_mode, int mode);

#endif /* XMOD_H_ */
