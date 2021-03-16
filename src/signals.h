#ifndef SIGNALS_H_
#define SIGNALS_H_

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "utils.h"
#include "logger.h"

#define STR_SIGINT "SIGINT"
#define STR_SIGUSR1 "SIGUSR1"
#define STR_SIGUSR2 "SIGUSR2"
#define STR_SIGTERM "SIGTERM"
#define STR_SIGSTOP "SIGSTOP"
#define STR_SIGCONT "SIGCONT"

#define EXIT_CTRLC 5

void registerAndIgnore(int sig);

void ctrlcReceived(int sig);

void displayInfo(int sig);

void questionPrompt(int sig);

void terminate(int sig);

#endif /* SIGNALS_H_ */
