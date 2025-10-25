#ifndef CURSOR_H
#define CURSOR_H

#include "file_info.h"
#include <stdlib.h>
#include <string.h>

#define SPACE_BETWEEN_LN_AND_TEXT 2;

typedef struct {
    int x;
    int y;
} cursor_pos;

void mvcurs(cursor_pos *cursor, file_info *file);
void init_cursor(cursor_pos *cursor, file_info *file);
void mvcurs_to_eol(cursor_pos *cursor, file_info *file);
int get_min_x(file_info *file);
int get_max_x(cursor_pos *cursor, file_info *file);

#endif
