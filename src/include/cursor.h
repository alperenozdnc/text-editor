#ifndef CURSOR_H
#define CURSOR_H

typedef struct {
    int x;
    int y;
} cursor_pos;

void init_cursor(cursor_pos *cursor);

#endif
