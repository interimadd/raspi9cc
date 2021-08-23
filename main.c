#include "9cc.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    user_input = argv[1];

    // トークナイズする
    token = tokenize(argv[1]);
    Node *node = expr();

    // アセンブリの前半部分を出力    
    printf(".text\n");
    printf(".globl main\n");
    printf("main:\n");

    // 抽象構文木を下りながらコード生成
    gen(node);

    printf("    pop {r0}\n");
    printf("    bx lr\n");
    return 0;
}