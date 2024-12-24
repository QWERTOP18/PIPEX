/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xunistd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:17:26 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 18:53:13 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"


int xopen(const char *path, int oflag, int mode)
{
	int    fd;

    fd = open(path, oflag, mode);
    if (fd == -1)
    {
        ft_putstr_fd(PROGRAM,2);
		ft_putstr_fd((char *)path,2);
		ft_putstr_fd(": ",2);
		ft_putstr_fd(strerror(errno),2);
    }
    return (fd);
}

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
