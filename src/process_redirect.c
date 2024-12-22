#include "pipex.h"


int process_redir_node(t_node *node, t_info *info)
{
    char path[PATH_MAX];
    int fd;
    if (fetch_absolutepath(path, node->u_val.file, info->env_path, F_OK))
    {
        perror(node->u_val.file);//bash: path: No such file or directory
        return;
    }

    if (node->e_type == TOKEN_REDIR_IN)
    {
        if (fd = open(path, O_RDONLY))
        {
            perror(path);
            return 127;
        }
        dup2(info->pipefds[1], fd);
        xclose(info->pipefds[1]);
    }
    if (node->e_type >> OUT & 1)
    {
        if (node->e_type == TOKEN_REDIR_OUT)
         fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    }




}