#include "9cc.h"

void gen(Node *node) {
    if (node->kind == ND_NUM) {
        printf("    mov r3, #%d\n", node->val);
        printf("    push {r3}\n", node->val);
        return;
    }

    gen(node->lhs);
    gen(node->rhs);

    printf("    pop {r1}\n");
    printf("    pop {r0}\n");

    switch (node->kind) {
        case ND_ADD:
            printf("    add r0, r1\n");
            break;
        case ND_SUB:
            printf("    sub r0, r1\n");
            break;
        case ND_MUL:
            printf("    mul r0, r1\n");
            break;
        case ND_DIV:
            printf("    str lr, [sp, #-4]!\n");
            printf("    bl  __divsi3\n");
            printf("    ldr lr, [sp], #4\n");
            printf("    bx  lr\n");
            break;
        case ND_EQUAL:
            printf("    cmp r0, r1\n");
            printf("    moveq r0, #1\n");
            printf("    movne r0, #0\n");
            break;
        case ND_NOTEQ:
            printf("    cmp r0, r1\n");
            printf("    moveq r0, #0\n");
            printf("    movne r0, #1\n");
            break;
        case ND_LESS:
            printf("    cmp r0, r1\n");
            printf("    movlt r0, #1\n");
            printf("    movge r0, #0\n");
            break;
        case ND_LESS_EQUAL:
            printf("    cmp r0, r1\n");
            printf("    movle r0, #1\n");
            printf("    movgt r0, #0\n");
            break;
    }

    printf("    push {r0}\n");
}