/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:38:49 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 19:08:25 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

pid_t	process_cmd(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	pid_t	pid;
	char	path[PATH_MAX];

	pid = xfork(info);
	if (pid == 0)
	{
		if (in_fd != -1)
		{
			dup2(in_fd, STDIN_FILENO);
			xclose(&in_fd);
		}
		if (out_fd != -1)
		{
			dup2(out_fd, STDOUT_FILENO);
			xclose(&out_fd);
		}
		if (fetch_absolutepath(path, *node->args, info->env_path, X_OK))
			process_exit();
		execve(path, node->args, info->env);
		process_exit();
	}
	return (pid);
}

void	process_pipe(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	int	pipefds[2];

	if (!node)
		return ;
	if (node->type == TOKEN_PIPE)
	{
		if (node->right != NULL)
		{
			if (pipe(pipefds) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			process_cmd(node->left, in_fd, pipefds[1], info);
			close(pipefds[1]);
			process_pipe(node->right, pipefds[0], out_fd, info);
		}
		else
		{
			waitpid(process_cmd(node->left, in_fd, out_fd, info), NULL, 0);
			close(in_fd); //どちらをcloseするべきか
		}
	}
}
