/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:17:23 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 10:44:54 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int	fetch_absolutepath(char path[], char *src, char **env_path, int mode)
{
	char temp_path[PATH_MAX];
	while (*env_path)
	{
		ft_strlcpy(temp_path, path[], PATH_MAX);
		printf("%s\n", *temp_path); // DEBUG
		if (access(argv[1], mode) == -1)
		{
		}
		env_path++;
	}
}