#include "system.h"


// t_btree *ftx_btree_create_node(void *item, void *sys_info)
// {
//     t_btree *node;
//     t_info *info = (t_info *)sys_info;

//     node = ft_btree_create_node(item);
//     if (!node)
//     {
//         if (info && info->__exit)
//         {
//             info->__exit(info, E_ALLOCATE);
//         }
//     }
//     return node;
// }

pid_t xfork(t_info *info)
{
    pid_t pid = fork();
    
    if (pid == -1) 
    {
        perror("fork");
        system_exit(info, errno);
    }
    return pid;  // 子プロセスは0、親プロセスは子プロセスIDを返す
}

void *xmalloc(size_t size, t_info *info)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        perror("malloc");
        system_exit(info, errno);
    }
    ft_memset(ptr, 0, size);
    return ptr;
}

void xpipe(int pipfds[],t_info *info)
{
    if (pipe(pipfds))
    {
        perror("pipe");
        system_exit(info, errno);
    }
}

void xfree(void **ptr)
{
    if (!ptr || *ptr == NULL)
    {
        return;
    }
    free(*ptr);
    *ptr = NULL;
}

int xclose(int *fd)
{
    if (!fd || *fd == -1)
    {
        return 0;
    }
    int ret = close(*fd);
    if (ret == -1)
    {
        perror("close");
    }
    *fd = -1;
    return ret;
}

