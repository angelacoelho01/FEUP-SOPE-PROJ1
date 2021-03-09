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

/**
 * Check if a specific path corresponds to a directory
 * @param path The location of the content to check
 * @return True if the path corresponds to a directory, false otherwise
 */
bool isPathDir(const char *path);

/**
 * Iterate a directory and change his content permissions, including himself
 * @param options Comand options
 * @param mode Comand new mode
 * @param dirpath The location of the directory to iterate
 * @return 0 when successfull, -1 otherwise
 */
int iterateDirectory(const char *options, const char *mode, const char *dirpath);

#endif /* _FILESYSTEM */
