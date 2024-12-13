#include "pipex.h"

int	main(int argc, char const **argv, char **env)
{
	int pipefd[2];
	int fd_filein;
	int fd_fileout;
	t_cmd *cmd;

	pipefd[0] = -1;
	pipefd[1] = -1;
	fd_filein = open(argv[1], O_RDONLY);
	fd_fileout = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0666);
	dup_stdin(fd_filein);
	while (*cmd)
	{
		pipe(pipefd); // fd[1] write & fd[0] read
		dup_stdout(pipefd[1]);
		handle_exec("cat", env);
		// read_file(pipefd[0]);
		dup_stdin(pipefd[0]);
	}
	dup_stdout(fd_fileout);
	handle_exec("wc -l", env);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}