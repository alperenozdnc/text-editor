#include <txtedt/charins.h>

#include <stdlib.h>
#include <string.h>

/*
 * `charins()` - stands for char insert. inserts at file->lines[[y]][[x]], grows
 * the line by 1 char, and leaves the rest of the line the same. its the
 * parents job to free the allocated memory.
 *
 * `@c`: the char to be inserted.
 * `@x`: the idx of the char.
 * `@y`: the idx of the line to be inserted to.
 */
void charins(file_info *file, char c, int x, int y) {
    char *ln = file->lines[y];

    size_t len = strlen(ln);

    // 1 for new char and 1 for \0 in + 2
    char *ln_new = malloc(len + 2);

    int j = 0;

    for (size_t i = 0; i < len; i++) {
        if ((int)i == x) {
            ln_new[j++] = c;
        }

        ln_new[j++] = ln[i];
    }

    if (x == (int)len) {
        ln_new[j++] = c;
    }

    ln_new[j] = '\0';

    free(file->lines[y]);
    file->lines[y] = strdup(ln_new);
    free(ln_new);
}
