#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <ctype.h>	

#define MAX_STR_LEN 256

/**
 * @brief Converts the value of a permission to a string.
 * 
 * @param perms the permission vlaue
 * @return char* the permission in form of a string
 */
char* convertPermsToString(const mode_t perms);

/**
 * @brief Checks if a given string represents a number.
 * 
 * @param str the string to check
 * @return 1 if the string is a number, 0 otherwise
 */
int isNumber(const char *str);

/**
 * @brief Checks if a given string contains a scpecific character.
 * 
 * @param possible_str the string to check
 * @param n the length of the string
 * @param ch the char to search for
 * @return 1 if the string constains the character, 0 otherwise
 */
int findChar(const char possible_str[], unsigned n, const char ch);

/**
 * @brief Gets the elapsed time in milliseconds since the Epoch.
 * 
 * @param start the start time of the program
 * @return double the time in milliseconds since the Epoch
 */
double getElapsedTime(const struct timespec start);

/**
 * @brief Gets the line arguments passed to call the program.
 * 
 * @param mode the mode
 * @param path the path
 * @param options the options
 */
void getLineArgs(const char *mode, const char *path, const char *options);

/**
 * @brief Waits and reads the response when CTRL+C is pressed: 'y' or 'n'.
 * 
 * @return the input
 */
char readAnswer(void);

/**
 * @brief Counts the number of occurrences of a certain character in a string.
 * 
 * @param str the string
 * @param ch the character to counter the number of occurrences
 * @return int the number of occurrences relative to the character
 */
int counterChar(const char* str, const char ch);

/**
 * @brief Turns all the characters from a string to upper case.
 * 
 * @param s the string to change all the chars to upper case
 */
void upperCase(char *s);

#endif /* UTILS_H_ */
