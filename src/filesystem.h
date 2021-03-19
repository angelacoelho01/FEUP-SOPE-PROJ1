#ifndef SRC_FILESYSTEM_H_
#define SRC_FILESYSTEM_H_

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
#include <signal.h>

#include "../src/xmod.h"
#include "../src/logger.h"
#include "../src/signals.h"

// Macro: Identify the content's type
#define TYPE_OTHER 0
#define TYPE_DIR 1
#define TYPE_LNK 2

/**
 * Checks wether the path is relative to directory, symbolic link or other.
 * 
 * @param path the path to check 
 * @return the number that identifies the type of the content the path represents
 */
int pathType(const char *path);

/**
 * Iterates through a directory and changes its content permissions, including itself.
 * 
 * @param options the command options
 * @param mode the new file permissions to add, remove or set
 * @param dirpath the directory path to iterate through
 * @return 0 on success, or -1 on error
 */
int iterateDirectory(const char *options, const char *mode, const char *dirpath);

#endif // SRC_FILESYSTEM_H_
