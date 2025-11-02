#include <txtedt/chardel.h>

#include <stdlib.h>
#include <string.h>

/*
 * `chardel()` - stands for char delete. deletes at file->lines[[y]][[x]],
 * decreases line by 1 char, and leaves the rest of the line the same. its the
 * parents job to free the allocated memory.
 *
 * `@x`: the idx of the char to be deleted.
 * `@y`: the idx of the line to be deleted from.
 */
void chardel(file_info *file, int x, int y) {
    char *ln = file->lines[y];

    // length is strlen(ln)
    // but actual length is strlen(ln) + 1 (including the null pointer)
    // so decreased length IS strlen(ln)
    size_t len = strlen(ln);
    char *ln_new = malloc(len);

    int j = 0;

    for (size_t i = 0; i < len; i++) {
        if ((int)i == x) {
            continue;
        }

        ln_new[j++] = ln[i];
    }

    ln_new[j] = '\0';

    free(file->lines[y]);
    file->lines[y] = strdup(ln_new);
    free(ln_new);
}
