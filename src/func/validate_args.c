#include <txtedt/validate_args.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool file_exists(const char *FILENAME) {
    return access(FILENAME, F_OK) == 0;
}

void create_file(const char *FILENAME) {
    // 5 -> touch
    // 1 -> space
    // +1 -> \0
    char *file_creation_cmd = malloc(5 + 1 + strlen(FILENAME) + 1);
    file_creation_cmd[0] = '\0';
    sprintf(file_creation_cmd, "touch %s", FILENAME);

    system(file_creation_cmd);

    free(file_creation_cmd);
}

/*
   * validate_args() - makes sure there is a file,
   * and only one file, and that it
   exists on the filesystem.

   @return: true if valid, false if invalid
*/
bool validate_args(int argc, const char *FILENAME) {
    if (argc < 2) {
        fprintf(stderr, "ERROR: no input files\n");

        return false;
    } else if (argc > 2) {
        fprintf(stderr, "ERROR: only one file allowed\n");

        return false;
    }

    if (!file_exists(FILENAME)) {
        create_file(FILENAME);

        return true;
    }

    return true;
}
