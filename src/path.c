/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:17:23 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 19:08:31 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int	fetch_absolutepath(char path[], char *src, char **env_path, int mode)
{
	char	temp_path[PATH_MAX];

	ft_strlcpy(path, src, PATH_MAX);
	if (src[0] == '/')
	{
		return (access(path, mode));
	}
	while (*env_path)
	{
		ft_strlcpy(temp_path, *env_path, PATH_MAX);
		ft_strlcat(temp_path, "/", PATH_MAX);
		ft_strlcat(temp_path, src, PATH_MAX);
		if (access(temp_path, mode) == 0)
		{
			ft_strlcpy(path, temp_path, PATH_MAX);
			return (0);
		}
		env_path++;
	}
	return (1); // file not found
}
