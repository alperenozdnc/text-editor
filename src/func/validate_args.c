#include "../include/validate_args.h"

bool file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
}

bool validate_args(int argc, const char *FILENAME) {
    if (argc < 2) {
        fprintf(stderr, "ERROR: no input files\n");

        return false;
    } else if (argc > 2) {
        fprintf(stderr, "ERROR: only one file allowed\n");

        return false;
    }

    if (!file_exists(FILENAME)) {
        fprintf(stderr, "ERROR: %s doesnt exist\n", FILENAME);

        return false;
    }

    return true;
}
