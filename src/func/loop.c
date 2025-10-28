#include "../include/loop.h"

/*
 * `loop()` - this is where the program lives. gets keypresses,
 * prints the lines, and moves the cursor for each loop.
 */
void loop(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    switch_terminal_mode(terminal);

    while (1) {
        if (recvkb(terminal, cursor, file) == -1) {
            break;
        }

        printl(terminal, cursor, file);
        mvcurs(terminal, cursor, file);
    }
}
