#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int		handle_exec(char *cmd, char **env);

void	read_file(int fd)
{
	char	buf[1024];
	int		ret;
	int		fdtest;

	fdtest = open("debug.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	ret = read(fd, buf, sizeof(buf));
	if (ret > 0)
		write(fdtest, buf, ret);
	close(fd);
	return ;
}

int	dup_stdin(int fd_filein)
{
	close(STDIN_FILENO);
	dup2(fd_filein, STDIN_FILENO);
	close(fd_filein);
	return (0);
}
int	dup_stdout(int fd_fileout)
{
	close(STDOUT_FILENO);
	dup2(fd_fileout, STDOUT_FILENO);
	close(fd_fileout);
	return (0);
}

int	main(int argc, char const **argv, char **env)
{
	int	pipefd[2];
	int	fd_filein;
	int	fd_fileout;

	pipefd[0] = -1;
	pipefd[1] = -1;
	fd_filein = open(argv[1], O_RDONLY);
	/*
	入力ファイルをSTDINにdup OK
	出力ファイルはO_TRUNCで初期化（UNLINLK)もしくはO_APPENDで追加
	*/
	fd_fileout = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0666);
	pipe(pipefd); // fd[1] write & fd[0] read
	dup_stdin(fd_filein);
	dup_stdout(pipefd[1]);
	handle_exec("ls -l", env);
	// read_file(pipefd[0]);
	dup_stdin(pipefd[0]);
	dup_stdout(fd_fileout);
	handle_exec("wc -l", env);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
