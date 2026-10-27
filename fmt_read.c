#include <stdio.h>
#include <string.h>

char leakme[] = "SECRET_LEAKME_1337";   /* global in .data */

int main(void) {
    char fmt[100];

    printf("leakme @ %p\n", (void*)leakme);
    printf("Enter format: ");
    if (fgets(fmt, sizeof(fmt), stdin) == NULL)
        return 1;

    size_t len = strlen(fmt);
    if (len > 0 && fmt[len - 1] == '\n')
        fmt[len - 1] = '\0';

    printf(fmt);
    return 0;
}
