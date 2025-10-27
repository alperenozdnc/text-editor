#include "../include/cursor.h"

void mvcurs(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    int min_x = get_min_x(file) + 1;
    int max_x = get_max_x(terminal, cursor, file) + 1;

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
    cursor->page = 1;
}

int get_min_x(file_info *file) {
    const int LINE_NUM_DIGITS_LEN = log10(file->line_count) + 1;

    return LINE_NUM_DIGITS_LEN + SPACE_BETWEEN_LN_AND_TEXT;
}

int get_max_x(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    const int LINE_LEN =
        strlen(file->lines[get_actual_y(terminal, cursor) - 1]);

    return get_min_x(file) + LINE_LEN - 1;
}

void mvcurs_to_eol(terminal_info *terminal, cursor_pos *cursor,
                   file_info *file) {
    cursor->x = get_max_x(terminal, cursor, file) + 1;
}

/*
 * converts a page-based y pos into an actual y pos for bound checking.
 * for example, for a terminal with 50 rows,
 * a page-based position could be (page 1, row 3).
 * but the actual position becomes 53
 */
int get_actual_y(terminal_info *terminal, cursor_pos *cursor) {
    return cursor->y + ((cursor->page) - 1) * terminal->row;
}
