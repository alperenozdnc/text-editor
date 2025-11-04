#include <txtedt/assert.h>
#include <txtedt/chardel.h>
#include <txtedt/charins.h>
#include <txtedt/clear.h>
#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/insrestd.h>
#include <txtedt/lndel.h>
#include <txtedt/lnins.h>
#include <txtedt/mv.h>
#include <txtedt/terminal.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int assert_count;
    int fail_count;
} test;

void init(test *ret, terminal_info *terminal, cursor_pos *cursor,
          file_info *file) {
    ret->assert_count = 0;
    ret->fail_count = 0;

    terminal->row = 5;

    init_file_info(terminal, file, "./file.c");
    init_cursor(cursor, file);
}

test __mv_down() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);

    // normal moving down
    assert(mv_down(&terminal, &cursor, &file), "mv_down ret true (y+1)");
    assert(cursor.y == 2, "mv_down should work (y+1)");

    // max bound
    cursor.y = file.line_count;
    assert(!mv_down(&terminal, &cursor, &file), "mv_down ret false (max+1)");

    // page logic
    cursor.y = terminal.row - 1;
    assert(mv_down(&terminal, &cursor, &file), "mv_down ret true (page+1)");
    assert(cursor.y == 1 && cursor.page == 2,
           "mv_down should change pages and pos (page+1)");

    free_file_info(&file);
    return ret;
}

test __mv_up() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);
    cursor.y = 2;

    // normal moving down
    assert(mv_up(&terminal, &cursor, &file), "mv_up ret true (y-1)");
    assert(cursor.y == 1, "mv_up should work (y-1)");

    // min bound
    cursor.y = 1;
    assert(!mv_up(&terminal, &cursor, &file), "mv_up ret false (min-1)");

    // page logic
    cursor.y = 1;
    cursor.page = 2;

    assert(mv_up(&terminal, &cursor, &file), "mv_up ret true (page-1)");
    assert(cursor.y == 4 && cursor.page == 1,
           "mv_down should change pages and pos (page-1)");

    free_file_info(&file);
    return ret;
}

test __mv_left() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);

    // normal moving left
    cursor.x = get_min_x(&file) + 2;
    int old_x = cursor.x;

    assert(mv_left(&terminal, &cursor, &file), "mv_left ret true (x-1)");
    assert(cursor.x == old_x - 1, "mv_left should work (x-1)");

    // min bound
    cursor.x = get_min_x(&file) + 1;
    assert(!mv_left(&terminal, &cursor, &file), "mv_left ret false (min-1)");

    free_file_info(&file);
    return ret;
}

test __mv_right() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);

    // normal moving right
    cursor.x = get_min_x(&file) + 1;
    int old_x = cursor.x;

    assert(mv_right(&terminal, &cursor, &file), "mv_right ret true (x+1)");
    assert(cursor.x == old_x + 1, "mv_right should work (x+1)");

    // max bound
    old_x = get_max_x(&terminal, &cursor, &file) + 1;
    cursor.x = old_x;

    assert(!mv_right(&terminal, &cursor, &file), "mv_right ret false (max+1)");

    free_file_info(&file);
    return ret;
}

test __lnins() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);

    // normal line insertion
    int old_size = file.line_count;

    lnins(&file, cursor.y);

    char *empty = "\n";

    assert(file.lines[old_size], "lnins adds lines");
    assert(strcmp(file.lines[cursor.y], empty) == 0, "lnins adds empty lines");
    assert(!file.lines[old_size + 1], "lnins adds only one line");
    assert(file.line_count == old_size + 1, "lnins updates line count");

    free_file_info(&file);
    return ret;
}

test __lndel() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);

    // normal line deletion
    int old_size = file.line_count;
    char *old_last_line = strdup(file.lines[old_size - 1]);

    lndel(&file, cursor.y);

    assert(&old_last_line != &file.lines[old_size - 1], "lndel deletes lines");
    assert(file.lines[old_size - 2], "lndel deletes only one line");
    assert(file.line_count == old_size - 1, "lndel updates line count");

    free_file_info(&file);
    free(old_last_line);

    return ret;
}

test __charins() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);

    // normal char insertion
    size_t old_size = strlen(file.lines[cursor.y - 1]);

    charins(&file, '`', cursor.x - 1, cursor.y - 1);

    size_t new_size = strlen(file.lines[cursor.y - 1]);

    assert(new_size == old_size + 1, "charins adds one char");
    assert(file.lines[cursor.y - 1][cursor.x - 1] == '`',
           "charins inserts at the right place");

    free_file_info(&file);

    return ret;
}

test __chardel() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);

    // normal char deletion
    size_t old_size = strlen(file.lines[cursor.y - 1]);
    char old_char = file.lines[cursor.y - 1][cursor.x - 1];

    chardel(&file, cursor.x - 1, cursor.y - 1);

    size_t new_size = strlen(file.lines[cursor.y - 1]);
    char new_char = file.lines[cursor.y - 1][cursor.x - 1];

    assert(new_size == old_size - 1, "chardel deletes one char");
    assert(new_char != old_char, "chardel deletes at the right place");

    free_file_info(&file);

    return ret;
}

test __insrestd() {
    test ret;
    terminal_info terminal;
    cursor_pos cursor;
    file_info file;

    init(&ret, &terminal, &cursor, &file);

    // normal line slicing, deleting, and inserting
    int oldlc = file.line_count;

    char *ln = strdup(file.lines[cursor.y]);
    size_t ln_size = strlen(ln);

    insrestd(&file, floor((float)ln_size / 2), cursor.y);

    assert(file.line_count == oldlc + 1, "insrestd inserts one line");

    assert(strlen(file.lines[cursor.y]) + strlen(file.lines[cursor.y + 1]) ==
               ln_size + 1,
           "insrestd splits correctly");

    free_file_info(&file);

    return ret;
}

int main() {
    test (*tests[])() = {__mv_down, __mv_up,   __mv_left, __mv_right, __lnins,
                         __lndel,   __charins, __chardel, __insrestd};
    size_t tests_len = sizeof(tests) / sizeof(tests[0]);

    int total_asserts = 0;
    int total_fails = 0;

    printf("======= TESTING SUITE =======\n\n");

    for (size_t i = 0; i < tests_len; i++) {
        test ret = tests[i]();

        total_asserts += ret.assert_count;
        total_fails += ret.fail_count;

        int total_passes = ret.assert_count - ret.fail_count;

        printf("%d out of %d passed\n", total_passes, ret.assert_count);
        printf("\n");
    }

    int total_passed = total_asserts - total_fails;

    printf("=============================\n\n");

    printf("%d out of %d passed -> %f%% \n", total_passed, total_asserts,
           (float)total_passed / total_asserts * 100);

    return 0;
}
