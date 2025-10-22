#include "../include/is_valid_args.h"
#include "../include/file_exists.h"

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
