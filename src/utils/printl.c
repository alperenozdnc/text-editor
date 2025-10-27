#include "../include/printl.h"

void print_info_line(terminal_info *terminal, cursor_pos *cursor,
                     file_info *file) {

    char file_and_pos_info[100];
    int actual_y = get_actual_y(terminal, cursor);

    sprintf(file_and_pos_info, "[%s @ (%.2d,%.2d)]", file->path, actual_y,
            cursor->x);

    char *key_info =
        pad_str_left(' ', terminal->col - strlen(file_and_pos_info),
                     "[<ctrl-c> exit, <ctrl-h> help]");

    if (actual_y >= file->line_count - terminal->row &&
        cursor->page * terminal->row > file->line_count) {
        int amount_of_lines = cursor->page * terminal->row - file->line_count;

        for (int i = 0; i < amount_of_lines; i++) {
            for (int j = 0; j < terminal->col; j++) {
                printf("~");
            }

            printf("\r\n");
        }
    }

    // weird escape codes are for making the background white
    printf("%c[%d;%dm%s%s%c[0m", 0x1B, 30, 47, file_and_pos_info, key_info,
           0x1B);
}

void printl(terminal_info *terminal, file_info *file, cursor_pos *cursor) {
    clear();

    int end = cursor->page * terminal->row;
    int begin = end - terminal->row;

    int max_ln_len = get_min_x(file) - SPACE_BETWEEN_LN_AND_TEXT;

    for (int i = 0; i < file->line_count; i++) {
        // cursor and terminal sizes are 1-based
        int one_based_i = i + 1;

        if (one_based_i < begin - 1) {
            continue;
        } else if (one_based_i > end - 1) {
            break;
        }

        char *line = file->lines[i];
        char idx_str[max_ln_len];
        sprintf(idx_str, "%d", i + 1);

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

    print_info_line(terminal, cursor, file);
}
