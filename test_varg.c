#include <stdarg.h>
#include <stdio.h>

// we can use any argument we want
int sum(int count, ...) {
    long this_not_leak = 0x1337;
    va_list ap;
    va_start(ap, count);

    int total = 0;
    for (int i = 0; i < count; i++)
        total += va_arg(ap, int);

    for (int i = 0 ; i < 20; i++) { 
        printf("%p\n", va_arg(ap, void*));
    }
    va_end(ap);
    return total;
}

int main() {
    long this_get_leak = 0x1338;
    printf("%d\n", sum(3, 10, 20, 30));
}

