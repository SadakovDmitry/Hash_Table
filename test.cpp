#include <stdint.h>
#include <stdio.h>

int main()
{
    char str[] = "hgcehcoeucvhue";
    size_t len = 0;

    asm (
        ".intel_syntax noprefix\n"

        "jmp .next\n"
        "mov rcx, 1\n"
        ".next:\n"

        ".att_syntax prefix\n"

        : "=r" (len)
        :
        : "%rcx"
    );

    printf("%lu\n", len);
    return 0;
}
