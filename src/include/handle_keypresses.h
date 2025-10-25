#ifndef HANDLE_KEYPRESSES_H
#define HANDLE_KEYPRESSES_H

#include "clear.h"
#include "cursor.h"
#include "file_info.h"
#include "printl.h"
#include "terminal.h"
#include "validate_args.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_ESC '\e'
#define KEY_EXIT 3

#define ARROW_UP 'A'
#define ARROW_DOWN 'B'
#define ARROW_LEFT 'D'
#define ARROW_RIGHT 'C'

void handle_keypresses(terminal_info *terminal, cursor_pos *cursor,
                       file_info *file);

#endif
