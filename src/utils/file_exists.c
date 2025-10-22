#include "../include/file_exists.h"

bool file_exists(const char *filename) { return access(filename, F_OK) == 0; }
