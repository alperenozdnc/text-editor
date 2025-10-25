#include "../include/file_info.h"
#include "../include/cleanup.h"

void init_file_info(terminal_info *terminal, file_info *file,
                    const char *path) {
    file->path = path;
    file->fptr = fopen(file->path, "r");
    file->lines = NULL;
    file->line_count = 0;

    if (file->fptr == NULL) {
        fprintf(stderr, "ERROR: could not open file\n");
        cleanup(terminal, file);

        exit(EXIT_FAILURE);
    }

    char buffer[MAX_ROW_SIZE];

    while (fgets(buffer, sizeof(buffer), file->fptr)) {
        file->lines =
            realloc(file->lines, (file->line_count + 1) * sizeof(char *));

        file->lines[file->line_count] = strdup(buffer);
        file->line_count++;
    }
}

void free_file_info(file_info *file) {
    fclose(file->fptr);

    for (int i = 0; i < file->line_count; i++) {
        free(file->lines[i]);
    }

    free(file->lines);
}
