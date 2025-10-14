#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("ERROR: no input files\n");

        return 1;
    } else if (argc > 2) {
        printf("ERROR: only one file allowed\n");

        return 1;
    }

    return 0;
}
