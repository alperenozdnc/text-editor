#include "printl.h"
#include <stdlib.h>

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

void printl(char lines[MAX_ROW_SIZE][MAX_COL_SIZE], size_t size) {
    char line_num_str[100];
    sprintf(line_num_str, "%d", (int)size);

    int max_ln_len = strlen(line_num_str) + 1;

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
