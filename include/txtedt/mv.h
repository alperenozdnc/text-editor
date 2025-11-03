#ifndef MV_H
#define MV_H

#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/ignore.h>
#include <txtedt/terminal.h>

#include <stdbool.h>

bool mv_up(terminal_info *terminal, cursor_pos *cursor, ignore file_info *_);
bool mv_down(terminal_info *terminal, cursor_pos *cursor, file_info *file);
bool mv_right(terminal_info *terminal, cursor_pos *cursor, file_info *file);
bool mv_left(ignore terminal_info *_, cursor_pos *cursor, file_info *file);

#endif
