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

    handle_keypresses(&cursor, &file);

    clear();

    free_file_info(&file);

    return 0;
}
