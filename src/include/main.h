#include "is_valid_args.h"
#include "printl.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mvcurs(x, y) printf("\033[%d;%dH", y, x)

#define set_raw() system("stty raw -echo")
#define set_canonical() system("stty cooked echo")

#define KEY_ESC '\e'
#define ARROW_UP 'k'
#define ARROW_DOWN 'j'
#define ARROW_LEFT 'h'
#define ARROW_RIGHT 'l'
