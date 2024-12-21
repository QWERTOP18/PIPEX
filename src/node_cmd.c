#include "libft.h"
#include "system.h"



void process_cmd_node(char **argv, t_info *info)
{
    // 引数をパース
    //　　変数展開　絶対パスの取得(access OK)
    if (!argv || !*argv)
        return;
    char path[PATH_MAX];
    if (fetch_absolutepath(path,argv[0], info->env_path, X_OK))
    {
        perror(argv[0]);//bash: argv[0]: command not found
        return;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        system_exit(info, errno);
    }
    else if (pid == 0) // 子プロセス
    {
        execve(path, argv, info->env);
        perror("execve");
        //ft_strs_clear(argv);//need ?
        exit(errno);//exit status?
    }
    else //親プロセス
    {
        //ft_strs_clear(argv);後でまとめて解放
    }

}