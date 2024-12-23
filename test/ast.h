#ifndef AST_H
#define AST_H

# include "../util/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define TOKEN_CMD 1
#define TOKEN_PIPE 2

typedef struct s_ast {
    int type;
    char **args;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;
t_ast *ast_new(char **argv);
void ast_clear(t_ast *node);
void print_ast(t_ast *node, int depth);
#endif