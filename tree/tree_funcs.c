#include "ft_system.h"


void consume_pipe(int pipefds[],t_info *info)
{
    if(pipe(pipefds))
    {
        perror("pipe");
        system_exit(info, errno);
    }
}

void u_consume_node(t_node *curr)
{
    
}

// t_btree *ft_btreenew(void *item)
// {
//     t_btree *new_node = malloc(sizeof(t_btree));
//     if(!new_node)
//         return NULL;
//     new_node->item = item;
//     new_node->left = NULL;
//     new_node->right = NULL;
//     return new_node;
// }


// int main(int argc, char **argv, char **env)
// {
    
//     return 0;
// }
