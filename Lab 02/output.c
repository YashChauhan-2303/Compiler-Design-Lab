#include <stdio.h>
#include <stdlib.h>

INT main() {
    INT a = 10;
    FLOAT b = 20.5;
    CHAR c = 'x';

    IF (a > 5) {
        printf("a is greater than 5\n");
    } ELSE {
        printf("a is not greater than 5\n");
    }

    FOR (INT i = 0; i < a; i++) {
        printf("Loop iteration %d\n", i);
    }

    RETURN 0;
}
