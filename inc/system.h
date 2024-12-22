/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:22 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 11:42:25 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SYSTEM_H
# define FT_SYSTEM_H
# include "../util/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

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
}				t_info;

typedef struct s_node
{
	// t_type type;
	enum
	{
		TOKEN_CMD,
		TOKEN_PIPE,
		TOKEN_EOF,
		TOKEN_REDIR_IN,
		TOKEN_REDIR_OUT,
		TOKEN_REDIR_APPEND,
		TOKEN_REDIR_HEREDOC,
		// TOKEN_ARGS,
		TOKEN_REDIRECT,
	} e_type;
	union
	{
		int		openfds;
		char	**argv;
		char	*file;
		int		pipefds[2];
	} u_val;
}				t_node;

#endif