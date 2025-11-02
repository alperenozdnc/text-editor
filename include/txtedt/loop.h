#ifndef LOOP_H
#define LOOP_H

#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/recvkb.h>
#include <txtedt/terminal.h>

void loop(terminal_info *terminal, cursor_pos *cursor, file_info *file);

#endif
