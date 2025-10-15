#include "utils/file_exists.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_valid_args(int argc, const char *FILENAME) {
    if (argc < 2) {
        printf("ERROR: no input files\n");

        return false;
    } else if (argc > 2) {
        printf("ERROR: only one file allowed\n");

        return false;
    }

    if (!file_exists(FILENAME)) {
        printf("ERROR: %s doesnt exist\n", FILENAME);

        return false;
    }

    return true;
}

int main(int argc, char **argv) {
    const char *FILENAME = argv[1];

    if (!is_valid_args(argc, FILENAME))
        return 1;

    return 0;
}
