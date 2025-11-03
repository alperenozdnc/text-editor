#ifndef RECVKB_H
#define RECVKB_H

#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/terminal.h>

#define KEY_ESC '\e'
#define KEY_EXIT 3
#define KEY_BACKSPACE 127
#define KEY_ENTER '\r'

#define CSI_BRACKET '['

#define ARROW_UP 'A'
#define ARROW_DOWN 'B'
#define ARROW_LEFT 'D'
#define ARROW_RIGHT 'C'

typedef enum { ACTION_EXIT, ACTION_IDLE, ACTION_PRINT } action_type;

action_type recvkb(terminal_info *terminal, cursor_pos *cursor,
                   file_info *file);

#endif
