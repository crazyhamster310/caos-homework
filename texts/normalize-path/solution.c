#include <stdio.h>

void normalize_path(char* path) {
    char* current_char = path;
    char* place_to_write = path;
    while (*current_char != '\0') {
        if (*current_char == '.') {
            if (*(current_char + 1) == '/') {
                current_char += 2;
                continue;
            }
            if (*(current_char + 1) == '.' && *(current_char + 2) == '/') {
                current_char += 3;
                if (place_to_write != path) {
                    --place_to_write;
                    while (place_to_write != path && *(place_to_write - 1) != '/') {
                        --place_to_write;
                    }
                    continue;
                }

            }
        } else if (*current_char == '/') {
            if (place_to_write != path && *(place_to_write - 1) == '/') {
                ++current_char;
                continue;
            }
        }
        *place_to_write++ = *current_char++;
    }
    *place_to_write = '\0';
}
