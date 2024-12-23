#include "ast.h"
#include <errno.h>
// 省略: error_exit, ft_calloc, astnew_node_cmd, astnew_node
pid_t process_cmd(t_ast *node, int in_fd, int out_fd) {
    
    pid_t pid = fork();
    if (pid == 0) {
        // 子プロセス
        printf("child in:  %d out:  %d\n",in_fd,out_fd);
        if (in_fd != -1) {
            dup2(in_fd, STDIN_FILENO);  // 標準入力をin_fdにリダイレクト
            close(in_fd);
        }
        if (out_fd != -1) {
            dup2(out_fd, STDOUT_FILENO);  // 標準出力をout_fdにリダイレクト
            close(out_fd);
        }
        
        if (execvp(node->args[0], node->args) == -1) {
            perror("execvp");
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
void exec_pipe(t_ast *node, int in_fd, int out_fd)
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
            process_cmd(node->left, in_fd, pipefds[1]);  // 標準入力をin_fdから、出力をpipefds[1]にリダイレクト
            close(pipefds[1]);  // 書き込み端を閉じる
            exec_pipe(node->right, pipefds[0],out_fd);  // 次のコマンドにパイプを渡す
        } else {
            // 最後のコマンドの場合
            waitpid(process_cmd(node->left, in_fd, out_fd),NULL,0);  // 最後のコマンドは標準出力にリダイレクトしない
            close(in_fd); //
        }
    }
}


void build(int argc, char **argv,char **env)
{
    
    int fd_in = open(argv[1],O_RDONLY);
    if(fd_in == -1)
    {
        perror("open input file");
    }
    int fd_out = open(argv[argc-1],O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if(fd_out == -1)
    {
        printf("%s: %s: %s\n", argv[0], argv[argc-1], strerror(errno));
    }
    argv[argc-1] = NULL; 
    t_ast *tree = ast_new(&argv[2]);
    printf("Abstract Syntax Tree:\n");
    print_ast(tree, 0);

    printf("\nExecuting command pipeline:\n");
    exec_pipe(tree, fd_in,fd_out);  // 最初は標準入力を渡さない
    while (wait(NULL) > 0);  // 全ての子プロセスが終了するのを待つ
    close(fd_in);
    close(fd_out);
    ast_clear(tree);
}


int main(int argc, char **argv,char **env) {
    if (argc == 1)
    {
        char *av[] = {"./pipex","infile","ls -l","cat","wc -l","outfile", NULL};
        int ac = sizeof(av)/sizeof(av[0]) - 1;
        //printf("%d\n",ac);
        build(ac, av, env);
        return 0;
    }
    build(argc, argv,env);
    
    return 0;
}
