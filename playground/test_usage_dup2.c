#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // リダイレクトするファイル名
    const char *filename = "output.txt";

    // ファイルを開く（書き込み用、存在しなければ作成、内容を上書き）
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 標準出力をファイルにリダイレクト
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return 1;
    }

    // fdはもう使わないので閉じる
    close(fd);

    // 以下の出力はすべて "output.txt" に書き込まれる
    printf("This output will go to the file instead of the terminal.\n");
    printf("dup2 makes it easy to redirect output.\n");

    return 0;
}
