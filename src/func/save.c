#include <txtedt/save.h>

void save(file_info *file) {
    file->fptr = freopen(file->path, "w", file->fptr);
    file->fptr = freopen(file->path, "a", file->fptr);

    for (int i = 0; i < file->line_count; i++) {
        fprintf(file->fptr, "%s", file->lines[i]);
    }
}
