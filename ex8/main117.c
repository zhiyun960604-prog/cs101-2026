#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int (*fp)(int, int) = add;
    printf("Result = %d\n", fp(3, 4));
    return 0;
}
