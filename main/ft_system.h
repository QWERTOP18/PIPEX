#ifndef FT_SYSTEM_H
#define FT_SYSTEM_H
#include <unistd.h>
#include <fcntl.h>
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
    t_status status;
    t_btree *root;
    char **env_path;
}t_info;

typedef enum e_type
{
    TOKEN_CMD,
    TOKEN_PIPE,
    TOKEN_EOF,
    // TOKEN_ARGS,
    TOKEN_FILEIN,
    TOKEN_FILEOUT,

} t_type;


typedef struct s_node {
    t_type type;
    union {
        char *args;
        int pipefds[2];
    } u_val;
} t_node;

#endif