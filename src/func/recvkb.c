#include <txtedt/chardel.h>
#include <txtedt/charins.h>
#include <txtedt/clear.h>
#include <txtedt/insrestd.h>
#include <txtedt/lndel.h>
#include <txtedt/lnins.h>
#include <txtedt/mv.h>
#include <txtedt/printl.h>
#include <txtedt/recvkb.h>
#include <txtedt/save.h>
#include <txtedt/validate_args.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * `handledel()` - stands for handle deletion.
 * handles char deletion, line
 * deletion, and edge cases
 *
 * `@return`: `true` if program should print, `false` if program should wait.
 * */
bool handledel(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    int zerobased_x = get_actual_x(cursor, file) - 1;
    int zerobased_y = get_actual_y(terminal, cursor) - 1;

    size_t line_len = strlen(file->lines[zerobased_y]);
    bool line_is_empty = (int)line_len == 1;

    bool is_char_deletion = zerobased_x >= 1;
    bool is_line_deletion = zerobased_x == 0 && line_is_empty;
    bool is_moving_line_up_by_deleting =
        zerobased_x == 0 && !line_is_empty && zerobased_y > 0;

    if (file->line_count == 1 && line_is_empty) {
        return false;
    }

    if (is_char_deletion) {
        chardel(file, zerobased_x - 1, zerobased_y);
        mv_left(terminal, cursor, file);

        return true;
    } else if (is_line_deletion) {
        lndel(file, zerobased_y);
        mv_up(terminal, cursor, file);

        cursor->x = get_max_x(terminal, cursor, file);
        mv_right(terminal, cursor, file);

        return true;
    } else if (is_moving_line_up_by_deleting) {
        int prev_line_is_empty = strlen(file->lines[zerobased_y - 1]) == 1;

        if (prev_line_is_empty) {
            lndel(file, zerobased_y - 1);
            mv_up(terminal, cursor, file);

            return true;
        } else {
            int ln_size = strlen(file->lines[zerobased_y]);
            int prev_ln_size = strlen(file->lines[zerobased_y - 1]);

            mv_up(terminal, cursor, file);

            for (int i = 0; i < ln_size; i++) {
                char c = file->lines[zerobased_y][i];

                if (c == '\n') {
                    continue;
                }

                charins(file, c, (prev_ln_size - 1) + i, zerobased_y - 1);
                mv_right(terminal, cursor, file);
            }

            lndel(file, zerobased_y);

            // moving left once because of the \n removed when deleting
            mv_left(terminal, cursor, file);

            return true;
        }
    }

    return false;
}

/*
 * `handleins()` - stands for handle insertion.
 * handles char insertion, line
 * insertion, and edge cases
 *
 * `@return`: `true` if program should print, `false` if program should wait.
 * */
bool handleins(terminal_info *terminal, cursor_pos *cursor, file_info *file,
               char ins_type) {
    int zerobased_x = get_actual_x(cursor, file) - 1;
    int zerobased_y = get_actual_y(terminal, cursor) - 1;
    int line_len = strlen(file->lines[zerobased_y]);

    if (ins_type == KEY_ENTER) {
        if (zerobased_x == 0) {
            lnins(file, zerobased_y);
        } else if (zerobased_x == line_len - 1) {
            lnins(file, zerobased_y + 1);
        } else {
            insrestd(file, zerobased_x, zerobased_y);
        }

        mv_down(terminal, cursor, file);

        cursor->x = get_min_x(file);
        mv_right(terminal, cursor, file);
    } else {
        charins(file, ins_type, zerobased_x, zerobased_y);
        mv_right(terminal, cursor, file);
    }

    return true;
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
                         file_info *file, char c) {
    bool ret = false;

    if (c == KEY_BACKSPACE) {
        ret = handledel(terminal, cursor, file);
    } else {
        ret = handleins(terminal, cursor, file, c);
    }

    return ret ? ACTION_PRINT : ACTION_IDLE;
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

    if (c == KEY_EXIT) {
        save(file);

        return ACTION_EXIT;
    }

    if (c == KEY_ESC) {
        if (getchar() == CSI_BRACKET) {
            return handlemov(terminal, cursor, file, getchar());
        }

        return ACTION_IDLE;
    }

    return handleinsdel(terminal, cursor, file, c);
}
