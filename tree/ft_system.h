#ifndef FT_SYSTEM_H
#define FT_SYSTEM_H
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "tree.h"

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

#endif