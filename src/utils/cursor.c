#include "../include/cursor.h"

void mvcurs(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void init_cursor(cursor_pos *cursor) {
    cursor->x = 1;
    cursor->y = 1;
}

int get_min_x(file_info *file) {
    const int LINE_NUM_DIGITS_LEN = log10(file->line_count) + 1;

    return LINE_NUM_DIGITS_LEN + SPACE_BETWEEN_LN_AND_TEXT;
}

int get_max_x(cursor_pos *cursor, file_info *file) {
    const int LINE_LEN = strlen(file->lines[cursor->y - 1]);

    return get_min_x(file) + LINE_LEN - 1;
}

void mvcurs_to_eol(cursor_pos *cursor, file_info *file) {
    cursor->x = get_max_x(cursor, file) + 1;
}
