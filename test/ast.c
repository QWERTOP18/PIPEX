#include "ast.h"

void error_exit(const char *message) 
{
    perror(message);
    exit(EXIT_FAILURE);
}

void *ft_calloc(size_t count, size_t size) 
{
    void *ptr = calloc(count, size);
    if (!ptr)
        error_exit("ft_calloc");
    return ptr;
}
t_ast *astnew_node(int type, char *argv) 
{
    t_ast *new_node = ft_calloc(1, sizeof(t_ast));
    new_node->type = type;
    new_node->args = ft_split(argv, ' ');
    return new_node;
}

t_ast *ast_new(char **argv)
{
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
void ast_clear(t_ast *node)
{
    if (!node)
        return;
    ast_clear(node->left);
    ast_clear(node->right);

    if (node->args)
    {
        ft_split_free(node->args);
    }
    free(node);
}
