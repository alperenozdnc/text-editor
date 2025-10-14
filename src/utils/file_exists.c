#include "file_exists.h"
#include <stdbool.h>
#include <unistd.h>

bool file_exists(const char *filename) { return access(filename, F_OK) == 0; }
