#ifndef LOOP_H
#define LOOP_H

#include "cursor.h"
#include "file_info.h"
#include "recvkb.h"
#include "terminal.h"

#include <stdbool.h>

void loop(terminal_info *terminal, cursor_pos *cursor, file_info *file);

#endif
