#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void execute_commands(const char *commands[][3], int num_commands, int curr_index, int prev_pipe[2]) {
    if (curr_index == num_commands) { // 全コマンドを処理した場合
        return;
    }

    int curr_pipe[2];
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
    execute_commands(commands, num_commands, curr_index + 1, curr_pipe);

    // 現在のパイプを閉じる
    if (curr_index < num_commands - 1) {
        close(curr_pipe[0]);
        close(curr_pipe[1]);
    }

    // 子プロセスを待つ
    int status;
    waitpid(pid, &status, 0);
    printf("Child process (PID %d) finished with status %d\n", pid, status);
}

int main() {
    const char *commands[][3] = {
        {"cat", NULL}, 
        {"cat", NULL}, 
        {"ls", NULL}
    };
    int num_commands = sizeof(commands) / sizeof(commands[0]);

    execute_commands(commands, num_commands, 0, NULL);

    return 0;
}
