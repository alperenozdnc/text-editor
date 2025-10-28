#include "../include/startup.h"

void startup(const char *FILENAME, terminal_info *terminal, cursor_pos *cursor,
             file_info *file) {
    init_terminal_info(terminal);
    init_file_info(terminal, file, FILENAME);
    init_cursor(cursor, file);

    printl(terminal, cursor, file);

    mvcurs(terminal, cursor, file);
}
