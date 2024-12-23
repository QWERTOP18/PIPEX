#include "ast.h"


void print_ast(t_ast *node, int depth) {
    if (!node)
        return;
    for (int i = 0; i < depth; i++)
        printf("  ");
    if (node->type == TOKEN_CMD)
        printf("CMD: %s\n", node->args[0]);
    else if (node->type == TOKEN_PIPE)
        printf("PIPE\n");
    
    // 左側と右側のノードを表示
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}








#ifdef PARSE
int main() {
    char *commands[] = {"ls", "cat", "grep .c", "wc -l", NULL};
    t_ast *tree = pipe_tree(commands);

    printf("Abstract Syntax Tree:\n");
    print_ast(tree, 0);

    return 0;
}
#endif
