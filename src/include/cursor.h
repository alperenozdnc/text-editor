#ifndef CURSOR_H
#define CURSOR_H

#include "file_info.h"
#include <stdlib.h>
#include <string.h>

#define SPACE_BETWEEN_LN_AND_TEXT 2;

/*
 * `struct cursor_pos` - holds the necessary info about the cursor position.
 * (all values are one-based)
 * `@x` - x axis
 * `@y` - y axis
 * `@page` - the page index
 */
typedef struct {
    int x;
    int y;
    int page;
} cursor_pos;

void mvcurs(terminal_info *terminal, cursor_pos *cursor, file_info *file);
void init_cursor(cursor_pos *cursor, file_info *file);
int get_min_x(file_info *file);
int get_max_x(terminal_info *terminal, cursor_pos *cursor, file_info *file);
int get_actual_y(terminal_info *terminal, cursor_pos *cursor);
int get_actual_x(cursor_pos *cursor, file_info *file);

#endif
