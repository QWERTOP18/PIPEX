#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	handle_exec(char *cmd, char **env);
int	main(int argc, char const **argv, char **env)
{
	int	fd[2];
	int	fd_filein;
	int	fd_fileout;

	fd[0] = -1;
	fd[1] = -1;
	fd_filein = open(argv[1], O_RDONLY);
	/*
	入力ファイルをSTDINにdup
	出力ファイルはO_TRUNCで初期化（UNLINLK)もしくはO_APPENDで追加
	*/
	fd_fileout = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	close(STDIN_FILENO); //いらないかも
	dup2(fd_filein, STDIN_FILENO);
	close(fd_filein);
	handle_exec("cat", env);
	// if (pipe(fd) == -1)
	// {
	// 	perror("pipe");
	// 	exit(1);
	// }
	return (0);
}
