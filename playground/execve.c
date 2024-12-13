#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char	**fetch_absolute_dir(char **env)
{
	char	*path;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 4) == 0)
		{
			path = *env + 4;
			return (ft_split(path, ':'));
		}
		env++;
	}
	return (NULL);
}

char	*fetch_exec_path(char **pathes, char *cmd_name)
{
	char	*exec_path;
	char	*with_slash_cmd_name;

	//  /をつける.splitのときに常に位置文字余らせておくとstrcatがつかえる
	with_slash_cmd_name = ft_strjoin("/", cmd_name);
	while (*pathes)
	{
		exec_path = ft_strjoin(*pathes, with_slash_cmd_name);
		// printf("%s\n", exec_path);
		if (access(exec_path, X_OK) == 0)
		{
			return (exec_path);
		}
		*pathes++;
	}
	return (NULL);
}
int	handle_exec(char *cmd, char **env)
{
	pid_t	pid;
	char	**absolute_path;
	char	**argvs;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		printf("Child process\n");
		absolute_path = fetch_absolute_dir(env);
		argvs = ft_split(cmd, ' ');
		path = fetch_exec_path(absolute_path, *argvs);
		// printf("strjoin %s\n", argvs[0]);
		if (argvs[0] == NULL)
		{
			printf("Command not found\n");
			exit(1); // freeするかしないか
		}
		if (access(path, X_OK) == -1)
		{
			perror("access");
			exit(1);
		}
		// char *argvs[] = {"ls", "-l", "../", 0};
		execve(path, argvs, env);
		// execve(argv[1], &argv[1], env);
	}
	printf("Parent process\n");
	(wait(NULL)); // wait(&status)
	return (0);
}

/*
./pipex "ls -l ../"
absolutepath = {"/usr/bin/",/usr/local/bin},
cmd_args = {"usr/bin/ls","-l","../"}
*/

#ifdef TEST_EXECVE
int	main(char const **argv, char **env)
{
	handle_exec(argc, argv[1], env);
	handle_exec(argc, argv[2], env);
	return (0);
}
#endif
