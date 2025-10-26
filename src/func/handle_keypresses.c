#include "../include/handle_keypresses.h"

void handle_keypresses(terminal_info *terminal, cursor_pos *cursor,
                       file_info *file) {
    switch_terminal_mode(terminal);

    while (1) {
        char c = getchar();

        if (c == KEY_EXIT) {
            break;
        }

        int curr_line_len = get_max_x(cursor, file);

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
                    if (get_actual_y(terminal, cursor) <=
                        file->line_count + 1) {
                        if (cursor->y == terminal->row - 1) {
                            cursor->page++;
                            cursor->y = 1;
                        } else {
                            cursor->y++;
                        }
                    }

                    break;
                case ARROW_RIGHT:
                    if (cursor->x <= curr_line_len) {
                        cursor->x++;
                    }

                    break;
                case ARROW_LEFT:
                    if (cursor->x - 1 > get_min_x(file)) {
                        cursor->x--;
                    }

                    break;
            }
        }

        printl(terminal, file, cursor);

        mvcurs(cursor, file);
    }
}
