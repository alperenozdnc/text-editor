#ifndef HANDLE_KEYPRESSES_H
#define HANDLE_KEYPRESSES_H

#include "clear.h"
#include "cursor.h"
#include "file_info.h"
#include "printl.h"
#include "validate_args.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define set_raw() system("stty raw -echo")
#define set_canonical() system("stty cooked echo")

#define KEY_ESC '\e'
#define ARROW_UP 'k'
#define ARROW_DOWN 'j'
#define ARROW_LEFT 'h'
#define ARROW_RIGHT 'l'

void handle_keypresses(cursor_pos *cursor, file_info *file);

#endif
