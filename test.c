#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main() {
    char arr[10] = "12345678";

    for (int i = 0; i < arr; ++i) {
        printf("%c\n", arr[i]);
    }

    return 0;
}