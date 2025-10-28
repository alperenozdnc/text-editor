#include "../include/terminal.h"

void init_terminal_info(terminal_info *terminal) {
    struct winsize window;

    // the cryptic TIOCGWINSZ is just a magic number that tells ioctl
    // to get the window size
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

    terminal->row = window.ws_row;
    terminal->col = window.ws_col;
    terminal->mode = TERM_MODE_COOKED;
};

void switch_terminal_mode(terminal_info *terminal) {
    if (terminal->mode == TERM_MODE_COOKED) {
        terminal->mode = TERM_MODE_RAW;

        system("stty raw -echo");
    } else {
        terminal->mode = TERM_MODE_COOKED;

        system("stty cooked echo");
    }
}
