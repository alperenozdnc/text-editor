#include <txtedt/chardel.h>
#include <txtedt/charins.h>
#include <txtedt/clear.h>
#include <txtedt/lndel.h>
#include <txtedt/lnins.h>
#include <txtedt/mv.h>
#include <txtedt/printl.h>
#include <txtedt/recvkb.h>
#include <txtedt/save.h>
#include <txtedt/validate_args.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    size_t dirsize = sizeof(exec) / sizeof(exec[0]);

    for (size_t i = 0; i < dirsize; i++) {
        if (input != keys[i]) {
            continue;
        }

        if (exec[i](terminal, cursor, file)) {
            return ACTION_PRINT;
        }
    }

    return ACTION_IDLE;
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
                return ACTION_IDLE;
            }

            if (zerobased_x >= 1) {
                chardel(file, zerobased_x - 1, zerobased_y);
                mv_left(terminal, cursor, file);

                return ACTION_PRINT;
            } else if (zerobased_x == 0 &&
                       strlen(file->lines[zerobased_y]) == 1) {
                lndel(file, zerobased_y);
                mv_up(terminal, cursor, file);

                cursor->x = get_max_x(terminal, cursor, file);
                mv_right(terminal, cursor, file);

                return ACTION_PRINT;
            } else {
                if (zerobased_x == 0 && strlen(file->lines[zerobased_y]) > 1 &&
                    zerobased_y > 0) {
                    if (strlen(file->lines[zerobased_y - 1]) == 1) {
                        file->line_count--;

                        lndel(file, zerobased_y - 1);
                        mv_up(terminal, cursor, file);

                        return ACTION_PRINT;
                    }
                }
            }

            break;
        case KEY_ENTER:
            if (zerobased_x != 0) {
                lnins(file, zerobased_y + 1);
            } else {
                lnins(file, zerobased_y);
            }

            mv_down(terminal, cursor, file);

            cursor->x = get_min_x(file);
            mv_right(terminal, cursor, file);

            return ACTION_PRINT;
        default:
            charins(file, input, zerobased_x, zerobased_y);
            mv_right(terminal, cursor, file);

            return ACTION_PRINT;
    }

    return ACTION_IDLE;
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

            return ACTION_IDLE;
        default:
            return handleinsdel(terminal, cursor, file, c);
    }
}
