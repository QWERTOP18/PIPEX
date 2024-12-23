#include "ast.h"

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void *ft_calloc(size_t count, size_t size) {
    void *ptr = calloc(count, size);
    if (!ptr)
        error_exit("ft_calloc");
    return ptr;
}
void print_ast(t_ast *node, int depth) {
    if (!node)
        return;
    for (int i = 0; i < depth; i++)
        printf("  ");
    if (node->type == TOKEN_CMD)
        printf("CMD: %s\n", node->argv);
    else if (node->type == TOKEN_PIPE)
        printf("PIPE\n");
    
    // 左側と右側のノードを表示
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}



t_ast *astnew_node(int type, char *argv) {
    t_ast *new_node = ft_calloc(1, sizeof(t_ast));
    new_node->type = type;
    new_node->argv = argv;
    return new_node;
}


t_ast *pipe_tree(char **argv) {
    t_ast *root_node = astnew_node(TOKEN_PIPE, NULL);
    t_ast *current_node = root_node;

    while (*argv != NULL) {
        current_node->left = astnew_node(TOKEN_CMD,*argv++);
        if (*argv)
            current_node->right = astnew_node(TOKEN_PIPE, NULL);
        current_node = current_node->right;
    }
    return root_node;
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
