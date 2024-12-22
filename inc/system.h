/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:22 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 15:28:47 by ymizukam         ###   ########.fr       */
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
}				t_info;
# define REDIRECT 4
typedef struct s_item
{
	// t_type type;
	enum
	{
		TOKEN_CMD,
		TOKEN_PIPE,
		TOKEN_EOF,
		TOKEN_REDIR_IN = 0b010000,
		TOKEN_REDIR_OUT = 0b010001,
		TOKEN_REDIR_APPEND = 0b010010,
		TOKEN_REDIR_HEREDOC = 0b010011,
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
}				t_item;

#endif