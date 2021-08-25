#include "9cc.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    user_input = argv[1];

    // トークナイズする
    token = tokenize(argv[1]);
    program();

    // アセンブリの前半部分を出力    
    printf(".text\n");
    printf(".globl main\n");
    printf("main:\n");

    // プロローグ
    // 変数26個分の領域を確保する
    printf("    push {fp}\n");
    printf("    mov fp, sp\n");
    printf("    sub sp, #208\n");

    // 先頭の式から順にコード生成
    for (int i = 0; code[i]; i++) {
        gen(code[i]);

        // 式の評価結果としてスタックに1つの値が残っているはずなので、スタックがあふれないようにポップしておく
        printf("    pop rax\n");
    }

    printf("    pop {r0}\n");
    printf("    bx lr\n");
    return 0;
}