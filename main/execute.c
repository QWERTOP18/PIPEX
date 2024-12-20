#include "libft.h"
#include "ft_system.h"


// int ast_traverse_dispather

void consume_pipe(int pipefds[],t_info *info)
{
    if(pipe(pipefds))
    {
        perror("pipe");
        system_exit(info, errno);
    }
    // close(pipefds[0]);
    // close(pipefds[1]);
}
void consume_cmd(char *args, t_info *info)
{


}
void consume_filein(char *args, t_info *info)
{
    // 入力を読み込む
    int fd = open(args[0], O_RDONLY);
    //errorハンドリング
    dup2(fd, STDIN_FILENO);
    close(fd);
}
int ast_traverse(t_btree *root, t_info *info)
{
    if (!root)
        return 0;
    if (info->status ==E_FATAL)
        return 1;
    t_node *node = root->item;
    if (node->type == TOKEN_EOF)
    {
        ast_traverse(root->left, info);
        return;
    }
   else if (node->type == TOKEN_CMD)
    {
        // 実行する
        ast_traverse(root->left,info);//FILEIN
        consume_cmd(node->u_val.args, info);
        ast_traverse(root->right, info);//FILEOUT
    }
    else if (node->type == TOKEN_PIPE)
    {
        // パイプする
        consume_pipe(root, info);//CMD
        ast_traverse(root->left, info);
        ast_traverse(root->right, info);//PIPE or CMD
    }
    else if (node->type == TOKEN_FILEIN)
    {
        consume_filein(node->u_val.args, info);
    }
    else if (node->type == TOKEN_FILEOUT)
    {
        consume_fileout(node->u_val.args, info);
    }
    return 0;
}