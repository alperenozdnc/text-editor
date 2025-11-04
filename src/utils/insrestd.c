#include <txtedt/charins.h>
#include <txtedt/insrestd.h>
#include <txtedt/lnins.h>

#include <stdlib.h>
#include <string.h>

/*
 * `insrestd()`: stands for insert rest down.
 *
 * copies all characters in lines[[y]] starting from x up until len,
 * inserts those characters into a new line and removes them from the
 * original line. */
void insrestd(file_info *file, int x, int y) {
    char *ln = file->lines[y];
    int line_len = strlen(ln);

    // no +1 for null terminator because newline won't be included
    char *sliced = malloc(line_len - x);
    int s = 0;

    // + 2 is for \n and \0
    int unsliced_size = x + 2;
    char *unsliced = malloc(unsliced_size);
    int u = 0;

    for (int i = 0; i < line_len; i++) {
        char c = ln[i];

        if (i < x) {
            unsliced[u++] = c;

            continue;
        }

        /* no newline because charins will respect
         * newlines when inserting 'sliced' */
        if (c == '\n') {
            continue;
        }

        sliced[s++] = c;
    }

    sliced[s] = '\0';

    unsliced[u] = '\n';
    unsliced[u + 1] = '\0';

    file->lines[y] = realloc(file->lines[y], unsliced_size);

    // all of the charins, lnins, lndel, ... funcs break down without a \0
    file->lines[y][0] = '\0';

    for (int i = 0; i < (int)strlen(unsliced); i++) {
        charins(file, unsliced[i], i, y);
    }

    lnins(file, y + 1);

    for (int i = 0; i < (int)strlen(sliced); i++) {
        charins(file, sliced[i], i, y + 1);
    }

    free(sliced);
    free(unsliced);
}
