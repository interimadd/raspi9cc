#include "9cc.h"

void gen_lval(Node *node) {
    if (node->kind != ND_LVAR)
        error("代入の左辺値が変数ではありません");
    
    printf("    mov r0, fp\n");
    printf("    sub r0, #%d\n", node->offset);
    printf("    push {r0}\n");
}

void gen(Node *node) {
    if (node->kind == ND_RETURN) {
        gen(node->lhs);
        printf("    pop {r0}\n");
        printf("    mov sp, fp\n");
        printf("    pop {fp}\n");
        printf("    bx  lr\n");
        return;
    }

    switch (node->kind) {
        case ND_NUM:
            printf("    mov r0, #%d\n", node->val);
            printf("    push {r0}\n", node->val);
            return;
        case ND_LVAR:
            gen_lval(node);
            printf("    pop {r0}\n");
            printf("    ldr r0, [r0]\n");
            printf("    push {r0}\n");
            return;
        case ND_ASSIGN:
            gen_lval(node->lhs);
            gen(node->rhs);

            printf("    pop {r1}\n");
            printf("    pop {r0}\n");
            printf("    str r1, [r0]\n");
            printf("    push {r1}\n");
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