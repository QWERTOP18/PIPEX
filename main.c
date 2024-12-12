/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:25:08 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/12 21:07:35 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#define PATH 5
#include "libft.h"

// debug
#include <stdlib.h>
#include <string.h>

char	**fetch_absolute_path(char **env)
{
	char	*path;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", PATH) == 0)
		{
			path = *env + PATH;
			return (ft_split(path, ':'));
		}
		env++;
	}
	return (NULL);
}

// int	main(int argc, char **argv, char **env)
// {
// 	int		pipe[2];
// 	char	**absolute_path;

// 	absolute_path = fetch_absolute_path(env);
// 	if (!absolute_path)
// 	{
// 		printf("Error: PATH variable not found in environment.\n");
// 		return (1);
// 	}
// }

#ifndef SAMPLE
int	main(int argc, char **argv, char **env)
{
	int		pipe[2];
	char	**absolute_path;
	char	*av[] = {"ls", "-l", NULL};
	pid_t	pid;

	/*
	./pipex file1 cmd1 cmd2 file2
	*/
	printf("%s\n\n", __DATE__);
	// if (argc < 5)
	// {
	// 	printf("Usage:./pipex file1 cmd1 cmd2 file2\n");
	// 	return (1);
	// }
	absolute_path = fetch_absolute_path(env);
	pid = fork();
	if (pid == 0)
	{
		printf("This is the child process!\n");
		if (access("/bin/ls", X_OK) == 0)
		{
			printf("%d\n", execve("/bin/ls", av, env));
			perror("execve:");
		}
		else
		{
			perror("access:");
		}
	}
	else
	{
		// This block is executed by the parent process
		printf("This is the parent process. Child PID is: %d\n", pid);
		wait(NULL); // Parent waits for the child to finish
	}
	printf("%s\n", absolute_path[0]);
	// to do make wrapper func of open
	// fd_from = open(argv[1], O_RDWR);
	// fd_to = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// if (fd_from == -1 || fd_to == -1)
	// {
	// 	perror("Error while opening files");
	// 	return (1);
	// }
	return (0);
}
#endif