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
            }

            // -1 in the bound is for the \n removed when deleting
            for (int i = 0; i < prev_ln_size - 1; i++) {
                mv_right(terminal, cursor, file);
            }

            lndel(file, zerobased_y);

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
                         file_info *file, char c, bool *changes_made) {
    bool ret = false;

    if (c == KEY_BACKSPACE) {
        ret = handledel(terminal, cursor, file);
    } else {
        ret = handleins(terminal, cursor, file, c);
    }

    if (ret) {
        *changes_made = true;
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
action_type recvkb(terminal_info *terminal, cursor_pos *cursor, file_info *file,
                   bool *changes_made) {
    char c = getchar();

    // start of line
    if (c == KEY_BEGIN) {
        cursor->x = get_min_x(file);

        return ACTION_PRINT;
    }

    // end of line
    if (c == KEY_END) {
        cursor->x = get_max_x(terminal, cursor, file) + 1;

        return ACTION_PRINT;
    }

    // end of file
    if (c == KEY_EOF) {
        while (mv_down(terminal, cursor, file)) {
        }

        return ACTION_PRINT;
    }

    // start of file
    if (c == KEY_SOF) {
        cursor->y = 1;
        cursor->page = 1;

        return ACTION_PRINT;
    }

    // move down one page
    if (c == KEY_INCP) {
        if (get_actual_y(terminal, cursor) + terminal->row <=
            file->line_count) {
            cursor->page++;
        }

        return ACTION_PRINT;
    }

    // move up one page
    if (c == KEY_DECP) {
        if (get_actual_y(terminal, cursor) - terminal->row >= 0) {
            cursor->page--;
        }

        return ACTION_PRINT;
    }

    // delete current line
    if (c == KEY_DELLINE) {
        if (file->line_count > 1) {
            lndel(file, get_actual_y(terminal, cursor) - 1);

            return ACTION_PRINT;
        }

        return ACTION_IDLE;
    }

    // save file
    if (c == KEY_SAVE) {
        save(file);

        *changes_made = false;

        return ACTION_IDLE;
    }

    // help menu
    if (c == KEY_HELP) {
        clear();

        printf("<ctrl-c>     exit txtedt\r\n");
        printf("<ctrl-s>     save current changes \r\n");
        printf("<ctrl-h>     display this menu\r\n");
        printf("\r\n");
        printf("<ctrl-z>     go to first in line\r\n");
        printf("<ctrl-x>     go to last in line\r\n");
        printf("\r\n");
        printf("<ctrl-s>     go to start of file\r\n");
        printf("<ctrl-e>     go to end of file\r\n");
        printf("\r\n");
        printf("<ctrl-u>     move one page up\r\n");
        printf("<ctrl-d>     move one page down\r\n");
        printf("\r\n");
        printf("<ctrl-r>     delete current line\r\n");
        printf("\r\n<any key>    go back to editing");

        if (getchar()) {
            return ACTION_PRINT;
        }
    }

    if (c == KEY_EXIT) {
        clear();

        char c = '\0';

        if (*changes_made == true) {
            printf("do you want to save changes (y/n)? ");

            char c = getchar();
        }

        if (c != '\0' && c != YES && c != YES - 32) {
            return ACTION_EXIT;
        }

        save(file);

        return ACTION_EXIT;
    }

    if (c == KEY_ESC) {
        if (getchar() == CSI_BRACKET) {
            return handlemov(terminal, cursor, file, getchar());
        }

        return ACTION_IDLE;
    }

    return handleinsdel(terminal, cursor, file, c, changes_made);
}
