#include <txtedt/save.h>

char uppercase(char c) {
    return c - 32;
}

void save(file_info *file) {
    clear();

    printf("do you want to save changes (y/n)? ");

    char c = getchar();

    if (c != YES && c != uppercase(YES)) {
        return;
    }

    file->fptr = freopen(file->path, "w", file->fptr);
    file->fptr = freopen(file->path, "a", file->fptr);

    for (int i = 0; i < file->line_count; i++) {
        fprintf(file->fptr, "%s", file->lines[i]);
    }
}
