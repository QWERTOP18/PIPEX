#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int pipefds[2];
    char buf[256] = {0};

    // パイプ作成
    if (pipe(pipefds) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid > 0) { // 親プロセス
        close(pipefds[0]); // パイプの読み取り側を閉じる
        printf("Parent process (PID: %d)\n", getpid());

        const char *message = "Message from parent to child.\n";
        write(pipefds[1], message, strlen(message)); // パイプに書き込み
        close(pipefds[1]); // 書き込み終了後にパイプを閉じる
    } else { // 子プロセス
        close(pipefds[1]); // パイプの書き込み側を閉じる
        printf("Child process (PID: %d)\n", getpid());

        ssize_t nbytes = read(pipefds[0], buf, sizeof(buf) - 1); // パイプから読み取り
        if (nbytes > 0) {
            buf[nbytes] = '\0'; // 文字列を正しく終端させる
            printf("Child received: %s", buf);
        }
        close(pipefds[0]); // 読み取り終了後にパイプを閉じる
    }

    return 0;
}
