#include "../include/cursor.h"

void mvcurs(cursor_pos *cursor, file_info *file) {
    int min_x = get_min_x(file) + 1;
    int max_x = get_max_x(cursor, file) + 1;

    if (cursor->x < min_x) {
        cursor->x = min_x;
    } else if (cursor->x > max_x) {
        cursor->x = max_x;
    }

    printf("\033[%d;%dH", cursor->y, cursor->x);
}

void init_cursor(cursor_pos *cursor, file_info *file) {
    cursor->x = get_min_x(file) + 1;
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
