#include <txtedt/mv.h>

bool mv_up(terminal_info *terminal, cursor_pos *cursor, ignore file_info *_) {
    if (cursor->y > 1) {
        cursor->y--;

        return true;
    }

    if (cursor->y == 1 && cursor->page > 1) {
        cursor->page--;
        cursor->y = terminal->row - 1;

        return true;
    }

    return false;
}

bool mv_down(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    if (get_actual_y(terminal, cursor) == file->line_count) {
        return false;
    }

    if (cursor->y == terminal->row - 1) {
        cursor->page++;
        cursor->y = 1;

        return true;
    } else {
        cursor->y++;

        return true;
    }

    return false;
}

bool mv_right(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    int max = get_max_x(terminal, cursor, file);

    if (cursor->x < max + 1) {
        cursor->x++;

        return true;
    }

    return false;
}

bool mv_left(ignore terminal_info *_, cursor_pos *cursor, file_info *file) {
    int min_x = get_min_x(file);

    if (cursor->x > min_x + 1) {
        cursor->x--;

        return true;
    }

    return false;
}
