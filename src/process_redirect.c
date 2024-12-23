/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:54 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 15:29:45 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "system.h"

int	process_redir_item(t_item *item, t_info *info)
{
	char path[PATH_MAX];
	int fd;
	if (item->e_type == TOKEN_REDIR_OUT || item->e_type == TOKEN_REDIR_APPEND)
	{
		if (item->e_type == TOKEN_REDIR_OUT)
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
		}
	}
	if (fetch_absolutepath(path, item->u_val.file, info->env_path, F_OK))
	{
		perror(item->u_val.file); // bash: path: No such file or directory
		return ;
	}

	if (item->e_type == TOKEN_REDIR_IN)
	{
		if (fd = open(path, O_RDONLY))
		{
			perror(path);
			return (127);
		}
		dup2(info->pipefds[1], fd);
		xclose(info->pipefds[1]);
	}
}