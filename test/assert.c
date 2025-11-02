#include <txtedt/assert.h>

#include <stdio.h>

void _assert(bool expr, char *msg, int *fail_count, int *assert_count) {
    (*assert_count)++;

    if (expr) {
        printf("%s[PASS]    %s%s\n", GREEN, msg, RESET);
    } else {
        printf("%s[FAIL]    %s%s\n", RED, msg, RESET);

        (*fail_count)++;
    }
}
