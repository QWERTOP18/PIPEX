#include "ast.h"
#include "system.h"
#include "xunistd.h"
pid_t process_cmd(t_ast *node, int in_fd, int out_fd, t_info *info) {
    
    pid_t pid = fork();
    if (pid == 0) {
        // 子プロセス
        printf("child in:  %d out:  %d\n",in_fd,out_fd);
        if (in_fd != -1)
        {
            dup2(in_fd, STDIN_FILENO);  // 標準入力をin_fdにリダイレクト
            xclose(&in_fd);
        }
        if (out_fd != -1)
        {
            dup2(out_fd, STDOUT_FILENO);  // 標準出力をout_fdにリダイレクト
            xclose(&out_fd);
        }
        char path[PATH_MAX];
        write(2, "aaa", 3);
        int acsees_ok = fetch_absolutepath(path, *node->args,info->env_path,X_OK); //
        fprintf(stderr, "node->%s\n", path);
        if (execve(path, node->args, info->env) == -1)
        {
            printf("pipex: %s: %s" ,node->args[0],strerror(errno));
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        // 親プロセス
        printf("Process %d %s\n",pid, node->args[0]);
        return pid;
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return -1;  // ここには来ない
}

// ASTを基にパイプラインを実行する関数
void exec_pipe(t_ast *node, int in_fd, int out_fd,t_info *info)
{
    if (!node || in_fd < 0 || out_fd < 0) 
    {
        return;
    }

    int pipefds[2];
    if (node->type == TOKEN_PIPE) {
        if (node->right != NULL) {
            if (pipe(pipefds) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            process_cmd(node->left, in_fd, pipefds[1],info);  // 標準入力をin_fdから、出力をpipefds[1]にリダイレクト
            close(pipefds[1]);  // 書き込み端を閉じる
            exec_pipe(node->right, pipefds[0],out_fd, info);  // 次のコマンドにパイプを渡す
        } else {
            // 最後のコマンドの場合
            waitpid(process_cmd(node->left, in_fd, out_fd, info),NULL,0);  // 最後のコマンドは標準出力にリダイレクトしない
            close(in_fd); //
        }
    }
}

