#ifndef PRINTL_H
#define PRINTL_H

#include "clear.h"
#include "cursor.h"
#include "file_info.h"
#include "pad_str_left.h"
#include "terminal.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printl(terminal_info *terminal, file_info *file, cursor_pos *cursor);

#endif
