#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef enum { TERM_MODE_COOKED, TERM_MODE_RAW } terminal_mode;

/*
 * `struct terminal_info` - holds the necessary info about the term window.
 * `@row` - the row count in characters
 * `@col` - the col count in characters
 * `@mode` - the terminal mode. 0 is for cooked and 1 is for raw.
 *
 * lookup `enum terminal_mode` in `include/terminal.h`
 */
typedef struct {
    int row;
    int col;
    terminal_mode mode;
} terminal_info;

void init_terminal_info(terminal_info *terminal);
void switch_terminal_mode(terminal_info *terminal);

#endif
