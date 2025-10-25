#ifndef FILE_INFO_H
#define FILE_INFO_H

#include "terminal.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *path;
    FILE *fptr;
    char **lines;
    int line_count;
} file_info;

#define MAX_ROW_SIZE 1000

void init_file_info(terminal_info *terminal, file_info *file, const char *path);
void free_file_info(file_info *file);

#endif
