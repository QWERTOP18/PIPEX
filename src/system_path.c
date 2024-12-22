/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:17:23 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 14:32:43 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"
#include <limits.h>

int	fetch_absolutepath(char path[], char *src, char **env_path, int mode)
{
	char temp_path[PATH_MAX];
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