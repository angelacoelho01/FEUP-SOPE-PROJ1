#ifndef _FILESYSTEM
#define _FILESYSTEM

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include <string.h>

#include "../permissions/xmod.h"

bool isPathDir(const char *path);

int iterateDirectory(const char* options, const char* mode, const char *dirpath, bool iterate_sub_dirs);

#endif /* _FILESYSTEM */
