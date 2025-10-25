#include "../include/cleanup.h"

void cleanup(terminal_info *terminal, file_info *file) {
    if (terminal->mode == TERM_MODE_RAW) {
        switch_terminal_mode(terminal);
    }

    free_file_info(file);

    clear();
}
