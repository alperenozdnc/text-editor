#include "../include/recvkb.h"

/*
 * `handlemov()` - handles cursor movement.
 *
 *
 * `@return`: `action_type` enum.
 * */
action_type handlemov(terminal_info *terminal, cursor_pos *cursor,
                      file_info *file, char input) {
    int curr_line_len = get_max_x(terminal, cursor, file);
    int actual_y = get_actual_y(terminal, cursor);
    int min_x = get_min_x(file);

    switch (input) {
        case ARROW_UP:
            if (cursor->y == 1 && cursor->page > 1) {
                cursor->page--;
                cursor->y = terminal->row - 1;

                return ACTION_PRINT;
            } else if (cursor->y > 1) {
                cursor->y--;

                return ACTION_PRINT;
            }

            break;
        case ARROW_DOWN:
            if (actual_y == file->line_count) {
                return ACTION_NORMAL;
            }

            if (cursor->y == terminal->row - 1) {
                cursor->page++;
                cursor->y = 1;

                return ACTION_PRINT;
            } else {
                cursor->y++;

                return ACTION_PRINT;
            }

            break;
        case ARROW_RIGHT:
            if (cursor->x > curr_line_len) {
                return ACTION_NORMAL;
            }

            cursor->x++;

            return ACTION_PRINT;
        case ARROW_LEFT:
            if (cursor->x <= min_x + 1) {
                return ACTION_NORMAL;
            }

            cursor->x--;

            return ACTION_PRINT;
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
                cursor->x--;

                return ACTION_PRINT;
            } else if (zerobased_x == 0 &&
                       strlen(file->lines[zerobased_y]) == 1) {
                lndel(file, zerobased_y);

                if (zerobased_y > 0) {
                    cursor->y--;
                }

                cursor->x = get_max_x(terminal, cursor, file) + 1;
                file->line_count--;

                return ACTION_PRINT;
            }

            break;
        case KEY_ENTER:
            if (zerobased_x != 0) {
                lnins(file, zerobased_y + 1);
            } else {
                lnins(file, zerobased_y);
            }

            cursor->y++;
            cursor->x = get_min_x(file) + 1;
            file->line_count++;

            return ACTION_PRINT;
        default:
            charins(file, input, zerobased_x, zerobased_y);

            cursor->x++;

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
