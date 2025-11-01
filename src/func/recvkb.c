#include "../include/recvkb.h"

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

/*
 * `handlemov()` - handles cursor movement.
 *
 * `@return`: `action_type` enum.
 * */
action_type handlemov(terminal_info *terminal, cursor_pos *cursor,
                      file_info *file, char input) {
    char keys[] = {ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT};
    bool (*exec[])(terminal_info *, cursor_pos *,
                   file_info *) = {mv_up, mv_down, mv_left, mv_right};

    for (int i = 0; i < 4; i++) {
        if (input != keys[i]) {
            continue;
        }

        if (exec[i](terminal, cursor, file)) {
            return ACTION_PRINT;
        }
    }

    return ACTION_NORMAL;
}

/*
 * `handleinsdel()` - handles insertion and deletion.
 *
 *
 * `@return`: `action_type` enum.
 * */
action_type handleinsdel(terminal_info *terminal, cursor_pos *cursor,
                         file_info *file, char input) {
    int zerobased_x = get_actual_x(cursor, file) - 1;
    int zerobased_y = get_actual_y(terminal, cursor) - 1;

    switch (input) {
        case KEY_BACKSPACE:
            if (file->line_count == 1) {
                return ACTION_NORMAL;
            }

            if (zerobased_x - 1 >= 0) {
                chardel(file, zerobased_x - 1, zerobased_y);
                mv_left(terminal, cursor, file);

                return ACTION_PRINT;
            } else if (zerobased_x == 0 &&
                       strlen(file->lines[zerobased_y]) == 1) {
                lndel(file, zerobased_y);
                file->line_count--;

                mv_up(terminal, cursor, file);

                cursor->x = get_max_x(terminal, cursor, file);

                mv_right(terminal, cursor, file);

                return ACTION_PRINT;
            }

            break;
        case KEY_ENTER:
            if (zerobased_x != 0) {
                lnins(file, zerobased_y + 1);
            } else {
                lnins(file, zerobased_y);
            }

            file->line_count++;

            mv_down(terminal, cursor, file);

            cursor->x = get_min_x(file);

            mv_right(terminal, cursor, file);

            return ACTION_PRINT;
        default:
            charins(file, input, zerobased_x, zerobased_y);

            mv_right(terminal, cursor, file);

            return ACTION_PRINT;
    }

    return ACTION_NORMAL;
}

/*
 * `recvkb()` - stands for receive keyboard. receives keypresses and updates the
 * cursor and the buffer accordingly.
 *
 *
 * `@return`: `action_type` enum.
 * */
action_type recvkb(terminal_info *terminal, cursor_pos *cursor,
                   file_info *file) {
    char c = getchar();

    switch (c) {
        case KEY_EXIT:
            save(file);

            return ACTION_EXIT;
        case KEY_ESC:
            if (getchar() == CSI_BRACKET) {
                return handlemov(terminal, cursor, file, getchar());
            }

            return ACTION_NORMAL;
        default:
            return handleinsdel(terminal, cursor, file, c);
    }
}
