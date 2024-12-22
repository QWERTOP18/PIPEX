/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:22 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 18:46:50 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SYSTEM_H
# define FT_SYSTEM_H
# include "../util/libft/libft.h"
# include "ast.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX = 1024
# endif
typedef enum e_status
{
	E_NONE,
	E_FATAL,
	E_ALLOCATE,

}				t_status;

typedef struct s_info
{
	t_status	status;
	t_btree		*root;
	char		**env;
	char		**env_path;
	// void		(*__exit)(void *, int);
	int			pipefds[2];
	t_pid_list	*pid_list;
}				t_info;

#endif