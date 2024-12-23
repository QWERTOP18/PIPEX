#include "ast.h"

// 省略: error_exit, ft_calloc, astnew_node_cmd, astnew_node
pid_t process_cmd(t_ast *node, int in_fd, int out_fd) {
    printf("Process %d %s\n",node->type, node->argv);
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
        
        char *args[] = {node->argv, NULL};  // コマンド引数
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        // 親プロセス
        return pid;
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return -1;  // ここには来ない
}

// ASTを基にパイプラインを実行する関数
void exec_pipe(t_ast *node, int in_fd) {
    if (!node) {
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
            exec_pipe(node->right, pipefds[0]);  // 次のコマンドにパイプを渡す
        } else {
            // 最後のコマンドの場合
            process_cmd(node->left, in_fd, -1);  // 最後のコマンドは標準出力にリダイレクトしない
        }
    }
}

// ASTを実行する関数
void exec_ast(t_ast *node) {
    exec_pipe(node, -1);  // 最初は標準入力を渡さない
    while (wait(NULL) > 0);  // 全ての子プロセスが終了するのを待つ
}


int main() {
    char *commands[] = {"ls","cat","wc", NULL};
    t_ast *tree = pipe_tree(commands);

    printf("Abstract Syntax Tree:\n");
    print_ast(tree, 0);

    printf("\nExecuting command pipeline:\n");
    exec_ast(tree);  // ASTに従ってコマンドを実行

    return 0;
}
