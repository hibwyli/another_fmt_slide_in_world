#include <stdio.h>
#include <string.h>

int main(void) {
    char fmt[100];
    int money = 0;

    printf("money @ %p = 0x%x\n", (void*)&money, money);
    printf("Enter format: ");
    if (fgets(fmt, sizeof(fmt), stdin) == NULL)
        return 1;

    size_t len = strlen(fmt);
    if (len > 0 && fmt[len - 1] == '\n')
        fmt[len - 1] = '\0';

    printf(fmt);
    printf("\n");

    if (money == 0xDEADBEEF) {
        printf("FLAG{money_set}\n");
    } else {
        printf("money = 0x%x (not DEADBEEF)\n", money);
    }
    return 0;
}