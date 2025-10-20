#include "printl.h"
#include <stdlib.h>

void printl(char lines[MAX_ROW_SIZE][MAX_COL_SIZE], size_t size) {
    for (size_t i = 0; i < size; i++) {
        char *line = lines[i];

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
