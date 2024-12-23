#ifndef AST_H
#define AST_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define TOKEN_CMD 1
#define TOKEN_PIPE 2
#define TOKEN_EOF 3

typedef struct s_ast {
    int type;
    char *argv;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;


void print_ast(t_ast *node, int depth);
t_ast *pipe_tree(char **argv);
#endif