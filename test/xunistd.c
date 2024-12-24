/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:17:26 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 15:36:50 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

pid_t	xfork(t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		system_exit(info, errno);
	}
	return (pid);
}

void	*xmalloc(size_t size, t_info *info)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		system_exit(info, errno);
	}
	ft_memset(ptr, 0, size);
	return (ptr);
}

void	xpipe(int pipfds[], t_info *info)
{
	if (pipe(pipfds))
	{
		perror("pipe");
		system_exit(info, errno);
	}
}

void	xfree(void **ptr)
{
	if (!ptr || *ptr == NULL)
	{
		return ;
	}
	free(*ptr);
	*ptr = NULL;
}

int	xclose(int *fd)
{
	int	ret;

	if (!fd || *fd == -1)
	{
		return (0);
	}
	ret = close(*fd);
	if (ret == -1)
	{
		perror("close");
	}
	*fd = -1;
	return (ret);
}
