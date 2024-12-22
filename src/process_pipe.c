/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:52 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 14:29:55 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "system.h"

void	setup_pipe(int pipefds[], t_info *info)
{
	if (pipe(pipefds))
	{
		perror("pipe");
		system_exit(info, errno);
	}
	info->pipefds[0] = pipefds[0];
	info->pipefds[1] = pipefds[1];
}
void	cleanup_pipe(int pipefds[], t_info *info)
{
	// Close the write end of the pipe
	xclose(&pipefds[1]);
	xclose(&pipefds[2]);
}