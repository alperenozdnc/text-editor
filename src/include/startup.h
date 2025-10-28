#ifndef STARTUP_H
#define STARTUP_H

#include "cursor.h"
#include "file_info.h"
#include "printl.h"
#include "terminal.h"

void startup(const char *FILENAME, terminal_info *terminal, cursor_pos *cursor,
             file_info *file);

#endif
