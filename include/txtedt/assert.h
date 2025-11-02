#ifndef ASSERT_H
#define ASSERT_H

#include <stdbool.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

#define PASS 0
#define FAIL 1

void _assert(bool expr, char *msg, int *fail_count, int *assert_count);
#define assert(expr, msg)                                                      \
    _assert(expr, msg, &ret.fail_count, &ret.assert_count);

#endif
