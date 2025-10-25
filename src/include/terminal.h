#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef enum { TERM_MODE_COOKED, TERM_MODE_RAW } terminal_mode;

typedef struct terminal_info_struct {
    int row;
    int col;
    terminal_mode mode;
} terminal_info;

void init_terminal_info(terminal_info *terminal);
void switch_terminal_mode(terminal_info *terminal);

#endif
