#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LOG printf("%s: %d\n",__func__,__LINE__);

void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if (argc < 5) // infile, at least one command, outfile
    {
        fprintf(stderr, "Usage: %s infile \"cmd1\" ... \"cmdN\" outfile\n", argv[0]);
        return 1;
    }

    int num_cmds = argc - 3; // Number of commands (excluding infile and outfile)
    int infilefd = open(argv[1], O_RDONLY);
    if (infilefd == -1)
        error_exit("infile");

    int outfilefd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfilefd == -1)
        error_exit("outfile");

    int pipefds[2];
    int prev_pipe_read = infilefd;

    for (int i = 0; i < num_cmds; i++)
    {
        if (i < num_cmds - 1) // Create a new pipe for intermediate commands
        {
            if (pipe(pipefds) == -1)
                error_exit("pipe");
        }

        pid_t pid = fork();
        if (pid == -1)
            error_exit("fork");

        if (pid == 0) // Child process
        {
            // Redirect input
            dup2(prev_pipe_read, STDIN_FILENO);
            close(prev_pipe_read);

            // Redirect output
            if (i < num_cmds - 1)
            {
                dup2(pipefds[1], STDOUT_FILENO);
                close(pipefds[0]);
                close(pipefds[1]);
            }
            else
            {
                dup2(outfilefd, STDOUT_FILENO);
            }

            // Parse the current command
            char *cmd_path = argv[i + 2];
            char *cmd_args[] = {cmd_path, NULL}; // Simplified for single-argument commands

            execvp(cmd_path, cmd_args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }

        // Parent process
        if (i > 0) // Close previous pipe read end
            close(prev_pipe_read);
        
        if (i < num_cmds - 1) // Close current pipe write end
        {
            close(pipefds[1]);
            prev_pipe_read = pipefds[0];
        }
    }

    close(outfilefd);
    // Wait for all child processes
    for (int i = 0; i < num_cmds; i++)
        wait(NULL);

    return 0;
}
