#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <txtedt/terminal.h>

#include <stdbool.h>
#include <stdio.h>

/*
 * `struct file_info` - holds the necessary info about the file buffer.
 *
 * `@path` - filesystem path of the file
 * `@fptr` - the pointer to the file stream
 * `@lines` - the 2d array that contain all lines seperated by a newline.
 * `@line_count` - sizeof lines
 * `@was_changed` - true if file was changed since startup, else false.
 */
typedef struct {
    const char *path;
    FILE *fptr;
    char **lines;
    int line_count;
    bool was_changed;
} file_info;

#define MAX_ROW_SIZE 1000

void init_file_info(terminal_info *terminal, file_info *file, const char *path);
void free_file_info(file_info *file);

#endif
