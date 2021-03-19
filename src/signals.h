#ifndef SIGNALS_H_
#define SIGNALS_H_

#include "utils.h"
#include "logger.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define STR_SIGINT "SIGINT"
#define STR_SIGUSR1 "SIGUSR1"
#define STR_SIGUSR2 "SIGUSR2"
#define STR_SIGTERM "SIGTERM"
#define STR_SIGSTOP "SIGSTOP"
#define STR_SIGCONT "SIGCONT"

#define EXIT_CTRLC 5

/**
 * @brief Sets all the signals handlers.
 * 
 */
void setUpSignals();

/**
 * @brief Registers the reception of signals to be ignored.
 * 
 * @param sig the received signal
 */
void registerAndIgnore(int sig);

/**
 * @brief Handles interrupts: order the children to write their information.
 * 
 * @param sig the received signal
 */
void ctrlcReceived(int sig);

/**
 * @brief Writes the process information on the screen and stops itself.
 * 
 * @param sig the received signal
 */
void displayInfo(int sig);

/**
 * @brief Confirms the termination of the program and operates according to the answer.
 * 
 * @param sig the received signal
 */
void questionPrompt(int sig);

/**
 * @brief Registers the termination of a process and exits it.
 * 
 * @param sig the received signal
 */
void terminate(int sig);

#endif /* SIGNALS_H_ */
