/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:54 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 14:32:35 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "system.h"

int	process_redir_node(t_node *node, t_info *info)
{
	char path[PATH_MAX];
	int fd;
	if (node->e_type == TOKEN_REDIR_OUT || node->e_type == TOKEN_REDIR_APPEND)
	{
		if (node->e_type == TOKEN_REDIR_OUT)
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
		}
	}
	if (fetch_absolutepath(path, node->u_val.file, info->env_path, F_OK))
	{
		perror(node->u_val.file); // bash: path: No such file or directory
		return ;
	}

	if (node->e_type == TOKEN_REDIR_IN)
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