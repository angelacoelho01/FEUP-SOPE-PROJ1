#ifndef INPUTCHECK_H_
#define INPUTCHECK_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "xmod.h"

/**
 * @brief Prints the program usage information.
 * 
 */
void usageNotRight();

/**
 * @brief Checks if the input provided on the command line is valid.
 * 
 * @param argc the number of arguments written in the command line
 * @param argv the array containing all the arguments passed on the execution of the program
 * @return 0 on success, or -1 if there is an InputError
 */
int isValidInput(int argc, char *argv[]);

#endif /* INPUTCHECK_H_ */
