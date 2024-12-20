#ifndef FT_SYSTEM_H
#define FT_SYSTEM_H
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "../libft/libft.h"

typedef enum e_status
{
    E_NONE,
    E_FATAL,
    E_ALLOCATE,

} t_status;

typedef struct s_info
{
    t_btree *root;
    char **env_path;
}t_info;

typedef enum e_type
{
    TOKEN_CMD,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_PIPE,
    TOKEN_ARGS,
    TOKEN_EOF,
} t_type;

typedef struct s_node
{
    t_type type;
    union u_val {
        char  *args;
        int    pipefds[2];
};
} t_node;
#endif