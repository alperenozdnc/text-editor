#include "../include/lndel.h"

/*
 * `lndel()` - stands for line delete. deletes the line at index y.
 * TODO: normally, line deletion in other editors work like 'inlining'
 * if characters behind cursor -> delete a char, if no characters behind cursor,
 * copy line, delete it, concat into the prev line,
 * if no characters behind cursor AND line size = 0, completely delete.
 */
void lndel(file_info *file, int y) {
    int len = file->line_count;

    size_t new_size = sizeof(char *) * (len - 1);
    char **new_lines = malloc(new_size);

    int j = 0;

    for (int i = 0; i < len; i++) {
        if (i == y) {
            continue;
        }

        new_lines[j++] = file->lines[i];
    }

    file->lines = realloc(file->lines, new_size);

    for (int i = 0; i < len - 1; i++) {
        char *new_line = new_lines[i];

        file->lines[i] = strdup(new_line);
    }

    free(new_lines);
}
