#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "permissions/xmod.h"
#include "filesystem/filesystem.h"
#include "inputcheck/inputcheck.h"

#define MAX_STR_LEN 256

int main(int argc, char *argv[], char *envp[]) {
    if (!isValidInput(argc, argv)) {
        usageNotRight();
        exit(INPUT_ERROR);
    }

    // With the valid input we can save the values without any problem

    char *mode = argv[argc - 2];
    char *path_name = argv[argc - 1];
    char *options = argc == 3 ? NULL : argv[1];
    int opt_R = 0;

    opt_R = options != NULL && strchr(options, 'R') != NULL ? 1 : 0;

    if (isPathDir(path_name) && opt_R) {
        // printf("It's a directory to iterate!\n");   // to test purposes

        if (iterateDirectory(options, mode, path_name) != 0) {
            fprintf(stderr, "Error changing dir's files permissions\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // printf("It's a single file/directory!\n");  // to test purposes

        if (xmod(options, mode, path_name) != 0) {
            fprintf(stderr, "Error changing file/directory's permissions\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
