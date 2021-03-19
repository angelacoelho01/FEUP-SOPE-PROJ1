#ifndef SRC_XMOD_H_
#define SRC_XMOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

#include "../src/utils.h"
#include "../src/logger.h"

#define MAX_STR_LEN 256

/**
 * @brief Changes a file or directory permissions.
 * 
 * @param options the options to the command execution
 * @param mode the new permissions to add, remove or set
 * @param path_name the path to the file or directory
 * @return int 0 on success, or -1 on error
 */
int xmod(const char *options, const char *mode, const char *path_name);

/**
 * @brief Responsible for handling and satisfy the options 'v' and 'c' and also modify nfmod variable when the file or directory permissions are changed.
 * 
 * @param options the options to handle: 'v' or 'c'
 * @param path_name the path to the file or directory
 * @param new_perms the new permissions of the file or directory
 * @return int 0 on success, or -1 on error
 */
int handleOptions(const char *options, const char *path_name, const mode_t new_perms);

/**
 * @brief Extracts which permissions must be modified in case mode is passed as a string.
 * 
 * @param mode the mode passed in the line arguments
 * @return char* the string with the permissions to be modified
 */
char *getStrPerms(const char *mode);

/**
 * @brief Get the new permissions to be setted.
 * 
 * @param mode the mode passed in the line arguments
 * @param path_name the path to the file or directory
 * @return mode_t the value relative to the new permissions
 */
mode_t getNewPerms(const char *mode, const char *path_name);

/**
 * @brief Resets the permissions value according to a certain user.
 * 
 * @param current_mode the current value relative to the permissions before changing
 * @param user the user: 'u'(user), 'g'(group), 'o'(other) or 'a'(all) that resets all the permissions
 * @return mode_t the new value relative to the permissions according to the changes made
 */
mode_t resetModeUser(const mode_t current_mode, const char user);

#endif // SRC_XMOD_H_
