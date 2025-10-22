#include "include/main.h"

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
    size_t lines_size = 0;

    while (fgets(buffer, buf_size, fptr)) {
        for (size_t j = 0; j < strlen(buffer); j++) {
            char str_c = buffer[j];
            lines[lines_size][j] = str_c;
        }

        lines_size++;
    }

    printl(lines, lines_size);

    cursor.x = strlen(lines[0]);
    mvcurs(cursor.x, cursor.y);

    char c;

    set_raw();

    while ((c = getchar()) != KEY_ESC) {
        getc(stdout);
        system("clear");

        char *curr_line = lines[cursor.y - 1];
        int curr_line_size = strlen(curr_line);

        switch (c) {
            case ARROW_UP:
                if (cursor.y > 1) {
                    cursor.y--;
                    cursor.x = strlen(lines[cursor.y - 1]);
                }

                break;
            case ARROW_DOWN:
                if (cursor.y <= (int)lines_size) {
                    cursor.y++;
                    cursor.x = strlen(lines[cursor.y - 1]);
                }

                break;
            case ARROW_LEFT:
                if (cursor.x > 1) {
                    cursor.x--;
                }

                break;
            case ARROW_RIGHT:
                if (cursor.x < curr_line_size) {
                    cursor.x++;
                }

                break;
            default:
                lines[cursor.y - 1][cursor.x] = c;

                cursor.x++;

                break;
        }

        printl(lines, lines_size);

        mvcurs(cursor.x, cursor.y);
    }

    set_canonical();

    system("clear");

    fclose(fptr);

    return 0;
}
