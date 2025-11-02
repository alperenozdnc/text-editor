#ifndef RECVKB_H
#define RECVKB_H

#include <txtedt/chardel.h>
#include <txtedt/charins.h>
#include <txtedt/clear.h>
#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/lndel.h>
#include <txtedt/lnins.h>
#include <txtedt/printl.h>
#include <txtedt/save.h>
#include <txtedt/terminal.h>
#include <txtedt/validate_args.h>

#include <stdbool.h>

#define ignore __attribute__((unused))

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

bool mv_up(terminal_info *terminal, cursor_pos *cursor, ignore file_info *_);
bool mv_down(terminal_info *terminal, cursor_pos *cursor, file_info *file);
bool mv_right(terminal_info *terminal, cursor_pos *cursor, file_info *file);
bool mv_left(ignore terminal_info *_, cursor_pos *cursor, file_info *file);

action_type recvkb(terminal_info *terminal, cursor_pos *cursor,
                   file_info *file);

#endif
