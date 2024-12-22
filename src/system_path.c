/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:17:23 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 14:37:01 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include <limits.h>

int	fetch_absolutepath(char path[], char *src, char **env_path, int mode)
{
	char temp_path[PATH_MAX];
	if (src[0] == '/')
	[
		ft_strlcpy(path, src, PATH_MAX);
        return (access(path,mode));
	]
	while (*env_path)
	{
		ft_strlcpy(temp_path, path, PATH_MAX);
		ft_strlcat(temp_path, "/", PATH_MAX);
		ft_strlcat(temp_path, env_path, PATH_MAX);
		printf("%s\n", *temp_path); // DEBUG
		if (access(temp_path, mode) == -1)
		{
		}
		env_path++;
	}
}