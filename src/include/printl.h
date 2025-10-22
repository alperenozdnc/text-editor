#ifndef PRINTL_H
#define PRINTL_H

#include "pad_str_left.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_SIZE 1000
#define MAX_COL_SIZE 1000

void printl(char lines[MAX_ROW_SIZE][MAX_COL_SIZE], size_t size);

#endif
