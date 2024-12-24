/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:57 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 19:23:10 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free(info);
	exit(status);
}

t_info	*system_init(char **env)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		exit(E_ALLOCATE);
	info->env = env;
	info->fd_in = -1;
	info->fd_out = -1;
	info->final_out = -1;
	while (env && *env)
	{
		if (strncmp(*env, "PATH=", strlen("PATH=")) == 0)
		{
			*env += strlen("PATH=");
			if (*env)
				info->env_path = ft_split(*env, ':');
			break ;
		}
		env++;
	}
	// if (!info->env_path)
	// 	info->env_path = ft_strdup("");
	return (info);
}

void	process_exit(void)
{
	ft_putstr_fd(ERRCMD,2);
	exit(EXIT_FAILURE);
}
