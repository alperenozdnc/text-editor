#define MAX_ROW_SIZE 1000
#define MAX_COL_SIZE 1000

#ifndef PRINTL_H
#define PRINTL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void printl(char lines[MAX_ROW_SIZE][MAX_COL_SIZE], size_t size);

#endif
