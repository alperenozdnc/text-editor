#ifndef RECVKB_H
#define RECVKB_H

#include "chardel.h"
#include "charins.h"
#include "clear.h"
#include "cursor.h"
#include "file_info.h"
#include "lndel.h"
#include "lnins.h"
#include "printl.h"
#include "terminal.h"
#include "validate_args.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_ESC '\e'
#define KEY_EXIT 3
#define KEY_BACKSPACE 127
#define KEY_ENTER '\r'

#define CSI_BRACKET '['

#define ARROW_UP 'A'
#define ARROW_DOWN 'B'
#define ARROW_LEFT 'D'
#define ARROW_RIGHT 'C'

typedef enum { ACTION_EXIT, ACTION_NORMAL, ACTION_PRINT } action_type;

action_type recvkb(terminal_info *terminal, cursor_pos *cursor,
                   file_info *file);

#endif
