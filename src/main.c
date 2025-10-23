#include "include/main.h"

int main(int argc, char **argv) {
    const char *FILENAME = argv[1];

    if (!validate_args(argc, FILENAME)) {
        return 1;
    }

    clear();

    file_info file;
    cursor_pos cursor;

    init_file_info(&file, FILENAME);
    init_cursor(&cursor);

    printl(&file);

    mvcurs_to_eol(&cursor, &file);
    mvcurs(cursor.x, cursor.y);

    char c;

    set_raw();

    while ((c = getchar()) != KEY_ESC) {
        clear();

        int curr_line_len = get_max_x(&cursor, &file);

        switch (c) {
            case ARROW_UP:
                if (cursor.y > 1) {
                    cursor.y--;
                    mvcurs_to_eol(&cursor, &file);
                }

                break;
            case ARROW_DOWN:
                if (cursor.y < file.line_count) {
                    cursor.y++;
                    mvcurs_to_eol(&cursor, &file);
                }

                break;
            case ARROW_LEFT:
                if (cursor.x - 1 > get_min_x(&file)) {
                    cursor.x--;
                }

                break;
            case ARROW_RIGHT:
                if (cursor.x <= curr_line_len) {
                    cursor.x++;
                }

                break;
        }

        printl(&file);
        printf("x = %d, y = %d", cursor.x, cursor.y);

        mvcurs(cursor.x, cursor.y);
    }

    set_canonical();

    clear();

    free_file_info(&file);

    return 0;
}
