#ifndef SIGNALS_H_
#define SIGNALS_H_

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

#include "../utils.h"


#define EXIT_CTRLC 5

void handler_ctrlc_parent(int sig);
void display_child_info(int sig);
void term_prompt(int sig);
void handler_term(int sig);

#endif /* SIGNALS_H_ */
