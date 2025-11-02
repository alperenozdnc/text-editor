#include <txtedt/cleanup.h>
#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/loop.h>
#include <txtedt/startup.h>
#include <txtedt/terminal.h>
#include <txtedt/validate_args.h>

int main(int argc, char **argv) {
    const char *FILENAME = argv[1];

    if (!validate_args(argc, FILENAME)) {
        return 1;
    }

    terminal_info terminal;
    file_info file;
    cursor_pos cursor;

    startup(FILENAME, &terminal, &cursor, &file);
    loop(&terminal, &cursor, &file);
    cleanup(&terminal, &file);

    return 0;
}
