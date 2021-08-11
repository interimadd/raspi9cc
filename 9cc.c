#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }
    
    char *p = argv[1];

    printf(".text\n");
    printf(".globl main\n");
    printf("main:\n");
    printf("    mov r0, #%ld\n", strtol(p, &p, 10));

    while (*p) {
        if (*p == '+') {
            p++;
            printf("    add r0, #%ld\n", strtol(p, &p, 10));
            continue;
        }
        if (*p == '-') {
            p++;
            printf("    sub r0, #%ld\n", strtol(p, &p, 10));
            continue;
        }

        fprintf(stderr, "予期しない文字列です： '%c'\n", *p);
    }

    printf("    bx lr\n");
    return 0;
}