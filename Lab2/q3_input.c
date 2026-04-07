#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 10;
    float b = 20.5;
    char c = 'x';

    if (a > 5) {
        printf("a is greater than 5\n");
    } else {
        printf("a is not greater than 5\n");
    }

    for (int i = 0; i < a; i++) {
        printf("Loop iteration %d\n", i);
    }

    return 0;
}
