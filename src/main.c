#include "utils/file_exists.h"

#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("ERROR: no input files\n");

        return 1;
    } else if (argc > 2) {
        printf("ERROR: only one file allowed\n");

        return 1;
    }

    const char *FILENAME = argv[1];

    if (!file_exists(FILENAME)) {
        printf("ERROR: %s doesnt exist\n", FILENAME);

        return 1;
    }

    return 0;
}
