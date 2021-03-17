#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "xmod.h"
#include "filesystem.h"
#include "inputcheck.h"
#include "signals.h"

#define MAX_STR_LEN 256

char *process_path;

int main(int argc, char *argv[], char *envp[]) {
    signal(SIGINT, ctrlcReceived); // handle ctrlc
    signal(SIGUSR1, registerAndIgnore); 
    signal(SIGUSR2, questionPrompt); // confirm exit
    signal(SIGTERM, terminate);

    // ignore other main signals, and be able to regist them
    signal(SIGHUP, registerAndIgnore);
    signal(SIGQUIT, registerAndIgnore);
    signal(SIGSEGV, registerAndIgnore);
    signal(SIGPIPE, registerAndIgnore);
    signal(SIGALRM, registerAndIgnore);
    signal(SIGCHLD, registerAndIgnore);

    // Check program call
    if (!isValidInput(argc, argv)) {
        usageNotRight();
        exit(INPUT_ERROR);
    }

    // With the valid input we can save the values without any problem
    char *mode = argv[argc - 2];
    char *path_name = argv[argc - 1];
    char *options = argc == 3 ? NULL : argv[1];
    int opt_R = options != NULL && strchr(options, 'R') != NULL ? 1 : 0;

    process_path = path_name;

    if ((pathType(path_name) == TYPE_DIR) && opt_R) {
        // directory to iterate
        if (iterateDirectory(options, mode, path_name) != 0) {
            fprintf(stderr, "Error changing dir's files permissions\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // single file/directory/symbolic link
        if (xmod(options, mode, path_name) != 0) {
            fprintf(stderr, "Error changing file/directory's permissions\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
