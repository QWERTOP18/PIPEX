/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:38:49 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 17:39:19 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

pid_t	process_cmd(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	pid_t	pid;
	char	path[PATH_MAX];
	int		access_ok;

	printf("Process CMD\n\n");
	pid = fork();
	if (pid == 0)
	{
		// 子プロセス
		printf("child in:  %d out:  %d\n", in_fd, out_fd);
		if (in_fd != -1)
		{
			dup2(in_fd, STDIN_FILENO); // 標準入力をin_fdにリダイレクト
			xclose(&in_fd);
		}
		if (out_fd != -1)
		{
			dup2(out_fd, STDOUT_FILENO); // 標準出力をout_fdにリダイレクト
			xclose(&out_fd);
		}
		write(2, "aaa", 3);
		access_ok = fetch_absolutepath(path, *node->args, info->env_path, X_OK);
		fprintf(stderr, "node->%s %d\n", path, access_ok);
		if (execve(path, node->args, info->env) == -1)
		{
			printf("pipex: %s: %s", node->args[0], strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		// 親プロセス
		printf("Process %d %s\n", pid, node->args[0]);
		return (pid);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (-1); // ここには来ない
}

// ASTを基にパイプラインを実行する関数
void	process_pipe(t_ast *node, int in_fd, int out_fd, t_info *info)
{
	int	pipefds[2];

	printf("Process PIPE\n\n");
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
			close(in_fd);
		}
	}
}
