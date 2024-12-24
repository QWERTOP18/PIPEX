/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:57 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 16:34:45 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "system.h"
#include <string.h> //debug

void	system_exit(t_info *info, int status)
{
	while (wait(NULL) > 0)
		;
	xclose(&info->fd_in);
	xclose(&info->fd_out);
	ft_strs_clear(info->env_path);
	ast_clear(info->root);
	// unlink(HEREDOC);
	exit(status);
}

t_info	*system_init(char **env)
{
	printf("system_initn");
	t_info *info = ft_calloc(1, sizeof(t_info));
	if (!info)
		exit(E_ALLOCATE);
	info->env = env;
	info->fd_in = -1;
	info->fd_out = -1;
	while (env && *env)
	{
		if (strncmp(*env, "PATH=", strlen("PATH=")) == 0)
		{
			*env += strlen("PATH=");
			printf("PATH=%s", *env);
			if (*env)
				info->env_path = NULL; // ft_split(*env, ':');
			break ;
		}
		env++;
	}
	// if (!info->env_path)
	// 	info->env_path = ft_strdup("");

	return (info);
}