#include "../include/printl.h"

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
}
