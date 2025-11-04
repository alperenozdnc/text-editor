#include <txtedt/ctrl.h>

/*
 * `ctrl()`: takes any char and returns the ASCII representation for ctrl+char.
 * */
int ctrl(char c) {
    return c & 0x1F;
}
