#include "../include/lnins.h"

/*
 * `lnins()` - stands for line insert. inserts a line at index y.
 * TODO: normally, line insertion in other editors work like 'slicing'.
 * if characters behind cursor -> create new line and concat all characters
 * after cursor to that line, if no characters behind cursor, just create a new
 * line.
 */
void lnins(file_info *file, int y) {
    int len = file->line_count;

    size_t new_size = sizeof(char *) * (len + 1);
    char **new_lines = malloc(new_size);

    int j = 0;

    for (int i = 0; i < len; i++) {
        if (i == y) {
            new_lines[j++] = "\n";
        }

        new_lines[j++] = file->lines[i];
    }

    file->lines = realloc(file->lines, new_size);

    for (int i = 0; i < len + 1; i++) {
        char *new_line = new_lines[i];

        file->lines[i] = strdup(new_line);
    }

    free(new_lines);
}
