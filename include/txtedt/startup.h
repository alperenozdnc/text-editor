#ifndef STARTUP_H
#define STARTUP_H

#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/printl.h>
#include <txtedt/terminal.h>

void startup(const char *FILENAME, terminal_info *terminal, cursor_pos *cursor,
             file_info *file);

#endif
