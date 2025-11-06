#include <txtedt/loop.h>
#include <txtedt/printl.h>
#include <txtedt/recvkb.h>

/*
 * `loop()` - this is where the program lives. gets keypresses,
 * prints the lines, and moves the cursor for each loop.
 */
void loop(terminal_info *terminal, cursor_pos *cursor, file_info *file) {
    switch_terminal_mode(terminal);

    bool changes_made = false;

    while (1) {
        action_type ret = recvkb(terminal, cursor, file, &changes_made);

        if (ret == ACTION_EXIT) {
            break;
        }

        if (ret == ACTION_PRINT) {
            printl(terminal, cursor, file, changes_made);
        }

        mvcurs(terminal, cursor, file);
    }
}
