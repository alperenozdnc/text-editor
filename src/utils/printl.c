#include "../include/printl.h"

char *pad_left(char fill_char, int len, char *initial_str) {
    char *output = malloc(sizeof(char) * len);

    int i = 0;
    int j = 0;

    while (i <= len) {
        if (i < len - (int)strlen(initial_str) - 1) {
            output[i] = fill_char;
        } else {
            output[i] = initial_str[j];
            j++;
        }

        i++;
    }

    return output;
}

int num_digit_count(int num) { return log10(num) + 1; }

void printl(char lines[MAX_ROW_SIZE][MAX_COL_SIZE], size_t size) {
    int max_ln_len = num_digit_count((int)size);

    for (size_t i = 0; i < size; i++) {
        char *line = lines[i];
        char idx_str[max_ln_len];
        sprintf(idx_str, "%d", (int)i + 1);

        char *line_num = pad_left(' ', max_ln_len, idx_str);

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
