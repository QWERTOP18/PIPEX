#ifndef FT_SYSTEM_H
#define FT_SYSTEM_H
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "../util/libft/libft.h"

typedef enum e_status
{
    E_NONE,
    E_FATAL,
    E_ALLOCATE,

} t_status;

typedef struct s_info
{
    t_status status;
    t_btree *root;
    char **env;
    char **env_path;
    void (*__exit)(void *, int);
}t_info;




typedef struct s_node {
    // t_type type;
    enum 
    {
        TOKEN_CMD,
        TOKEN_PIPE,
        TOKEN_EOF,
        // TOKEN_ARGS,
        TOKEN_REDIRECT,
    } e_type;
    union {
        char *args;
        int pipefds[2];
    } u_val;
} t_node;

#endif