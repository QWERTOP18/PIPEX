/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:25:08 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/05 00:45:59 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv, char **env)
{
	int fd1;
	int fd2;
	/*
	./pipex file1 cmd1 cmd2 file2
	*/

	if (argc < 4)
	{
		printf("Usage:./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}

	// to do make wrapper func of open
	fd1 = open(argv[1], O_RDWR);
	fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error while opening files");
		return (1);
	}
}