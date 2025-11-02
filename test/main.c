#include <txtedt/assert.h>
#include <txtedt/cursor.h>
#include <txtedt/file_info.h>
#include <txtedt/recvkb.h>
#include <txtedt/terminal.h>

#include <stdlib.h>

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
    assert(mv_down(&terminal, &cursor, &file), "mv_down ret true (page + 1)");
    assert(cursor.y == 1 && cursor.page == 2,
           "mv_down should change pages and pos (page + 1)");

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

    assert(mv_up(&terminal, &cursor, &file), "mv_up ret true (page - 1)");
    assert(cursor.y == 4 && cursor.page == 1,
           "mv_down should change pages and pos (page - 1)");

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

    return ret;
}

int main() {
    test (*tests[])() = {__mv_down, __mv_up, __mv_left, __mv_right};
    size_t tests_len = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < tests_len; i++) {
        test ret = tests[i]();

        printf("%d out of %d correct\n", ret.assert_count - ret.fail_count,
               ret.assert_count);
        printf("\n");
    }

    return 0;
}
