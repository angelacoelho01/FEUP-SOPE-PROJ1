#ifndef _SIGNALS
#define _SIGNALS

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "../utils.h"

#define EXIT_CTRLC 5

void ctrlcReceived(int sig);

void displayInfo(int sig);

void questionPrompt(int sig);

void terminate(int sig);

#endif /* _SIGNALS */
