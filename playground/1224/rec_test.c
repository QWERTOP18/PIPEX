#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void execute_pipeline(const char *commands[][3], int num_commands, int curr_index, int prev_pipe[2], const char *input_file, const char *output_file) {
    int curr_pipe[2];

    // 最初のコマンドの場合、入力リダイレクトを設定
    if (curr_index == 0 && input_file) {
        int infd = open(input_file, O_RDONLY);
        if (infd == -1) {
            error_exit("open input file");
        }
        dup2(infd, STDIN_FILENO);
        close(infd);
    }

    // 最後のコマンドの場合、出力リダイレクトを設定
    if (curr_index == num_commands - 1 && output_file) {
        int outfd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfd == -1) {
            error_exit("open output file");
        }
        dup2(outfd, STDOUT_FILENO);
        close(outfd);
    }

    // パイプを設定（最後のコマンド以外）
    if (curr_index < num_commands - 1) {
        if (pipe(curr_pipe) == -1) {
            error_exit("pipe");
        }
    }

    pid_t pid = fork();
    if (pid == -1) {
        error_exit("fork");
    }

    if (pid == 0) { // 子プロセス
        // 標準入力をリダイレクト（最初以外）
        if (curr_index > 0) {
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }

        // 標準出力をリダイレクト（最後以外）
        if (curr_index < num_commands - 1) {
            dup2(curr_pipe[1], STDOUT_FILENO);
            close(curr_pipe[0]);
            close(curr_pipe[1]);
        }

        // コマンドを実行
        execvp(commands[curr_index][0], (char *const *)commands[curr_index]);
        error_exit("execvp");
    }

    // 親プロセスは不要なパイプを閉じる
    if (curr_index > 0) {
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }

    // 再帰的に次のコマンドを実行
    if (curr_index < num_commands - 1) {
        execute_pipeline(commands, num_commands, curr_index + 1, curr_pipe, input_file, output_file);
    }

    // 現在のプロセスを待つ
    int status;
    waitpid(pid, &status, 0);
}

int main() {
    const char *commands[][3] = {
        {"cat", NULL},
        {"ls", NULL},
        {"grep", ".c", NULL}
    };

    const char *input_file = "inf";
    const char *output_file = "outf";

    int num_commands = sizeof(commands) / sizeof(commands[0]);

    execute_pipeline(commands, num_commands, 0, NULL, input_file, output_file);

    return 0;
}
