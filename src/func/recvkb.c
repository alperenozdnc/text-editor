#include "../include/recvkb.h"

/*
 * `recvkb()` - stands for receive keyboard. receives keypresses and updates the
 * cursor and the buffer accordingly.
 *
 *
 * @return: 0 if the main loop should continue running, and -1 if it should
 * stop.
 */
int recvkb(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    char c = getchar();
    int curr_line_len = get_max_x(terminal, cursor, file);

    if (c == KEY_EXIT) {
        return -1;
    }

    int actual_y = get_actual_y(terminal, cursor);
    int min_x = get_min_x(file);

    int zerobased_x = get_actual_x(cursor, file) - 1;
    int zerobased_y = actual_y - 1;

    if (c == KEY_ESC && getchar() == '[') {
        switch (getchar()) {
            case ARROW_UP:
                if (cursor->y == 1 && cursor->page > 1) {
                    cursor->page--;
                    cursor->y = terminal->row - 1;
                } else if (cursor->y > 1) {
                    cursor->y--;
                }

                break;
            case ARROW_DOWN:
                if (actual_y == file->line_count) {
                    break;
                }

                if (cursor->y == terminal->row - 1) {
                    cursor->page++;
                    cursor->y = 1;
                } else {
                    cursor->y++;
                }

                break;
            case ARROW_RIGHT:
                if (cursor->x > curr_line_len) {
                    break;
                }

                cursor->x++;

                break;
            case ARROW_LEFT:
                if (cursor->x <= min_x + 1) {
                    break;
                }

                cursor->x--;

                break;
        }

        return 0;
    }

    if (c == KEY_BACKSPACE) {
        if (zerobased_x - 1 >= 0) {
            chardel(file, zerobased_x - 1, zerobased_y);
            cursor->x--;
        } else if (zerobased_x == 0 && strlen(file->lines[zerobased_y]) == 1) {
            lndel(file, zerobased_y);

            if (zerobased_y > 0) {
                cursor->y--;
            }

            cursor->x = get_max_x(terminal, cursor, file) + 1;
        }
    } else if (c == '\r') {
        if (zerobased_x != 0) {
            lnins(file, zerobased_y + 1);
        } else {
            lnins(file, zerobased_y);
        }

        cursor->y++;
        cursor->x = min_x + 1;
    } else {
        charins(file, c, zerobased_x, zerobased_y);

        cursor->x++;
    }

    return 0;
}
