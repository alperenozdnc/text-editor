#include "utils/is_valid_args.h"
#include "utils/printl.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mvcurs(x, y) printf("\033[%d;%dH", (y), (x))

#define set_raw() system("stty raw")
#define set_canonical() system("stty cooked")

#define KEY_ESC '\e'
#define ARROW_UP 'k'
#define ARROW_DOWN 'j'
#define ARROW_LEFT 'h'
#define ARROW_RIGHT 'l'

typedef struct {
    int x;
    int y;
} cursor_pos;

void init_cursor(cursor_pos *cursor) {
    cursor->x = 1;
    cursor->y = 1;
}

int main(int argc, char **argv) {
    const char *FILENAME = argv[1];

    if (!is_valid_args(argc, FILENAME))
        return 1;

    system("clear");

    FILE *fptr = fopen(FILENAME, "r");
    int buf_size = 100;
    char buffer[buf_size];

    cursor_pos cursor;
    init_cursor(&cursor);

    char lines[MAX_ROW_SIZE][MAX_COL_SIZE] = {};
    int i = 0;

    while (fgets(buffer, buf_size, fptr)) {
        for (size_t j = 0; j < strlen(buffer); j++) {
            char str_c = buffer[j];
            lines[i][j] = str_c;
        }

        i++;
    }

    printl(lines);
    mvcurs(cursor.x, cursor.y);

    char c;

    set_raw();

    while ((c = getchar()) != KEY_ESC) {
        getc(stdout);
        system("clear");

        printl(lines);

        switch (c) {
            case ARROW_UP:
                cursor.y--;
                break;
            case ARROW_DOWN:
                cursor.y++;
                break;
            case ARROW_LEFT:
                cursor.x--;
                break;
            case ARROW_RIGHT:
                cursor.x++;
                break;
        }

        mvcurs(cursor.x, cursor.y);
    }

    set_canonical();

    system("clear");

    fclose(fptr);

    return 0;
}
