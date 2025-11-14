#ifndef RECVKB_H
#define RECVKB_H

#include <txtedt/ctrl.h>
#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/terminal.h>

#include <stdbool.h>

#define KEY_ESC '\e'
#define KEY_EXIT ctrl('c')
#define KEY_BACKSPACE 127
#define KEY_ENTER '\r'
#define KEY_BEGIN ctrl('z')
#define KEY_END ctrl('x')
#define KEY_EOF ctrl('e')
#define KEY_SOF ctrl('s')
#define KEY_INCP ctrl('d')
#define KEY_DECP ctrl('u')
#define KEY_DELLINE ctrl('r')
#define KEY_HELP ctrl('h')
#define KEY_SAVE ctrl('w')

#define CSI_BRACKET '['

#define ARROW_UP 'A'
#define ARROW_DOWN 'B'
#define ARROW_LEFT 'D'
#define ARROW_RIGHT 'C'

typedef enum { ACTION_EXIT, ACTION_IDLE, ACTION_PRINT } action_type;

action_type recvkb(terminal_info *terminal, cursor_pos *cursor,
                   file_info *file);

#endif
