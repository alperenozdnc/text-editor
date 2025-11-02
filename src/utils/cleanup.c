#include <txtedt/cleanup.h>
#include <txtedt/clear.h>

/*
 * `cleanup()` - unallocates allocated memory and clears the term.
 */
void cleanup(terminal_info *terminal, file_info *file) {
    if (terminal->mode == TERM_MODE_RAW) {
        switch_terminal_mode(terminal);
    }

    free_file_info(file);

    clear();
}
