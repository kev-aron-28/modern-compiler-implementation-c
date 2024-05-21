#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/Utils.h"

char* Substring(String source, int start, int length) {
    // Ensure the starting index and length are valid
    if (start < 0 || length < 0 || start + length > strlen(source)) {
        return NULL;
    }

    // Allocate memory for the substring (+1 for null terminator)
    String sub = (String)malloc(length + 1);
    if (sub == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Copy the substring
    strncpy(sub, source + start, length);

    // Null-terminate the substring
    sub[length] = '\0';

    return sub;
}
