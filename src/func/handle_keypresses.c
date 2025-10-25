#include "../include/handle_keypresses.h"

void handle_keypresses(cursor_pos *cursor, file_info *file) {
    set_raw();

    while (1) {
        char c = getchar();

        if (c == KEY_EXIT) {
            break;
        }

        int curr_line_len = get_max_x(cursor, file);

        if (c == KEY_ESC && getchar() == '[') {
            switch (getchar()) {
                case ARROW_UP:
                    if (cursor->y > 1) {
                        cursor->y--;
                        mvcurs_to_eol(cursor, file);
                    }

                    break;
                case ARROW_DOWN:
                    if (cursor->y < file->line_count) {
                        cursor->y++;
                        mvcurs_to_eol(cursor, file);
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

        clear();
        printl(file);

        printf("x = %d, y = %d", cursor->x, cursor->y);

        mvcurs(cursor->x, cursor->y);
    }

    set_canonical();
    clear();
}
