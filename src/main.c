#include "include/main.h"

int main(int argc, char **argv) {
    const char *FILENAME = argv[1];

    if (!validate_args(argc, FILENAME)) {
        return 1;
    }

    terminal_info terminal;
    file_info file;
    cursor_pos cursor;

    startup(FILENAME, &terminal, &cursor, &file);

    handle_keypresses(&terminal, &cursor, &file);

    cleanup(&terminal, &file);

    return 0;
}
