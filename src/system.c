/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:57 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 11:43:57 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include <string.h> //debug

// t_btree *node_item_new(t_type type, )
// {
// }

void	system_exit(t_info *info, int status)
{
	strs_free(info->env_path);
	// ft_btree_clear(info->root, );
	exit(status);
}

t_info	*system_init(char **env)
{
	t_info *info = malloc(sizeof(t_info));
	if (!info)
		exit(E_ALLOCATE);
	ft_memset(info, 0, sizeof(t_info));
	// info->__exit = ft_system_exit;
	info->pipefds[0] = -1;
	info->pipefds[1] = -1;
	info->env = env;
	// info->root = btree_create_node(NULL);
	while (env && *env)
	{
		if (strncmp(*env, "PATH=", strlen("PATH=")) == 0)
		{
			*env += strlen("PATH=");
			if (*env)
				info->env_path = ft_split(env, ' ');
			// info->env_path = xsplit(env,' ',info);
			break ;
		}
		env++;
	}
	if (!info->env_path)
		info->env_path = ft_strdup("");

	return (info);
}