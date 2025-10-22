#include "../include/pad_str_left.h"

char *pad_str_left(char fill_char, int len, char *initial_str) {
    char *output = malloc(sizeof(char) * len);

    int i = 0;
    int j = 0;

    while (i <= len) {
        if (i < len - (int)strlen(initial_str) - 1) {
            output[i] = fill_char;
        } else {
            output[i] = initial_str[j];
            j++;
        }

        i++;
    }

    return output;
}
