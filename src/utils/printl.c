#include "printl.h"

void printl(char lines[MAX_ROW_SIZE][MAX_COL_SIZE]) {
    for (size_t i = 0; i < strlen(*lines); i++) {
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
