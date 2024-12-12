#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char	**fetch_absolute_path(char **env)
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

/*
./pipex "ls -l ../"
absolutepath = {"/usr/bin/",/usr/local/bin},
cmd_args = {"usr/bin/ls","-l","../"}
*/
int	main(int argc, char **argv, char **env)
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		printf("Child process\n");

		char **absolute_path = fetch_absolute_path(env);
		while (*absolute_path)
		{
			printf("%s\n", *absolute_path);
			absolute_path++;
		}
		exit(0);
		if (access(argv[1], X_OK) == -1)
		{
			perror("access");
			exit(1);
		}
		execve(argv[1], &argv[1], env);
	}

	printf("Parent process\n");
	(wait(NULL)); // wait(&status)
	// {
	// 	perror("wait");
	// 	return (1);
	// }

	return (0);
}