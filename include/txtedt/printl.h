#ifndef PRINTL_H
#define PRINTL_H

#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/terminal.h>

#include <stdbool.h>

void printl(terminal_info *terminal, cursor_pos *cursor, file_info *file,
            bool changes_made);

#endif
