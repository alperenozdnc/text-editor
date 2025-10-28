#include "../include/printl.h"

/*
 * `print_info_line()` - prints the info line.
 * contains the cursor positions, the help menu
 *
 * and the shortcut for exiting the program.
 */
void print_info_line(terminal_info *terminal, cursor_pos *cursor,
                     file_info *file, int begin, int end) {

    char file_and_pos_info[100];
    int actual_y = get_actual_y(terminal, cursor);
    int actual_x = get_actual_x(cursor, file);

    sprintf(file_and_pos_info, "[%s @ (%.2d,%.2d), viewing (%d, %d)]",
            file->path, actual_y, actual_x, begin + 1, end - 1);

    char *key_info =
        pad_str_left(' ', terminal->col - strlen(file_and_pos_info),
                     "[<ctrl-c> exit, <ctrl-h> help]");

    int ESCAPE_CHAR = 0x1b;
    int FG = 37;
    int BG = 100;

    if (end > file->line_count) {
        // starting i from 1 because file->line_count is 1-based and end isnt
        for (int i = 1; i < end - file->line_count; i++) {
            printf("~\r\n");
        }
    }

    // weird escape codes are for making the background white
    printf("%c[%d;%dm%s%s%c[0m", ESCAPE_CHAR, FG, BG, file_and_pos_info,
           key_info, 0x1B);
}

/*
 * `printl()` - stands for print lines, prints the lines in buffer
 *
 * and the info line in the last row.
 */
void printl(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    clear();

    int end = cursor->page * terminal->row - (cursor->page - 1);
    int begin = end - terminal->row;

    int max_ln_len = get_min_x(file) - SPACE_BETWEEN_LN_AND_TEXT;

    for (int i = 0; i < file->line_count; i++) {
        // cursor and terminal sizes are 1-based
        int one_based_i = i + 1;

        if (one_based_i <= begin) {
            continue;
        } else if (one_based_i >= end) {
            break;
        }

        char *line = file->lines[i];
        char idx_str[max_ln_len];
        sprintf(idx_str, "%d", one_based_i);

        char *line_num = pad_str_left(' ', max_ln_len, idx_str);

        printf("%s  ", line_num);
        free(line_num);

        for (size_t j = 0; j < strlen(line); j++) {
            char c = line[j];

            if (c != '\n') {
                printf("%c", c);
                continue;
            }

            printf("\r\n");
        }
    }

    print_info_line(terminal, cursor, file, begin, end);
}
