#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define WR 1
#define RD 0
// typedef struct s_fds
// {
//     int pipefds[2];
//     int fdin;
//     int fdout;

// } t_fds;

#define LOG printf("%s: %d\n", __func__, __LINE__);

char *cmd1path = "/bin/cat";
char *cmd1args[] = { "cat", NULL };
char *cmd2path = "/usr/bin/grep";
char *cmd2args[] = { "grep", "a", NULL };


int main(int argc, char **argv)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s infile \"cmd1\" \"cmd2\" outfile\n", argv[0]);
        return 1;
    }

    int pipefds[2];
    if (pipe(pipefds) == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Open files
    int infilefd = open(argv[1], O_RDONLY);
    if (infilefd == -1)
    {
        perror("infile");
        exit(1);
    }
    //bonusの場合はAPPEND
    int outfilefd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfilefd == -1)
    {
        perror("outfile");
        exit(1);
    }

    // Fork for cmd1
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0) // Child process for cmd1
    {
        // Redirect stdin to infile
        dup2(infilefd,STDIN_FILENO);
        close(infilefd);

        // Redirect stdout to pipe write end
        dup2(pipefds[1], STDOUT_FILENO);
        close(pipefds[0]);
        close(pipefds[1]);

        execv(cmd1path, cmd1args);
        perror("execv cmd1");
        exit(1);
    }

    // Parent process: close infile and pipe write end
    close(infilefd);
    close(pipefds[1]);

    // Fork for cmd2
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0) // Child process for cmd2
    {
        // Redirect stdin to pipe read end
        dup2(pipefds[0], STDIN_FILENO);
        close(pipefds[0]);

        // Redirect stdout to outfile
        dup2(outfilefd, STDOUT_FILENO);
        close(outfilefd);

        execv(cmd2path, cmd2args);
        perror("execv cmd2");
        exit(1);
    }

    // Parent process: close pipe read end and outfile
    close(pipefds[0]);
    close(outfilefd);

    // Wait for child processes to finish
    wait(NULL);
    wait(NULL);

    return 0;
}
