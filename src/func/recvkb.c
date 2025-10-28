#include "../include/recvkb.h"

/*
 * recvkb() - stands for receive keyboard. receives keypresses and updates the
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
                if (get_actual_y(terminal, cursor) == file->line_count) {
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
                if (cursor->x - 1 <= get_min_x(file)) {
                    break;
                }

                cursor->x--;

                break;
        }
    }

    return 0;
}
