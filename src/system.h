/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:22 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 19:22:45 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_H
# define SYSTEM_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# ifndef PATH_MAX
#  define PATH_MAX = 1024
# endif

# define ERRCMD "command not found"
# define ERRDIR "Is a directory"

# define TOKEN_CMD 1
# define TOKEN_PIPE 2

typedef struct s_ast
{
	int				type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef enum e_status
{
	E_NONE,
	E_FATAL,
	E_ALLOCATE,
}					t_status;

typedef struct s_info
{
	t_status		status;
	t_ast			*root;
	char			**env;
	char			**env_path;
	int				fd_in;
	int				fd_out;
	int				final_out;
}					t_info;

void				process_exit(void);
void				system_exit(t_info *info, int status);
t_info				*system_init(char **env);
int					fetch_absolutepath(char path[], char *src, char **env_path,
						int mode);

/**** **** **** **** **** **** **** **** ****/
/**** **** **** *AST  library* **** **** ****/
/**** **** **** **** **** **** **** **** ****/
t_ast				*ast_new(char **argv, t_info *info);
void				ast_clear(t_ast *node);
void				print_ast(t_ast *node, int depth);

/**** **** **** **** **** **** **** **** ****/
/**** **** **  eXtended library  ** **** ****/
/**** **** **** **** **** **** **** **** ****/
void				xfree(void **ptr);
int					xclose(int *fd);
void				xpipe(int pipfds[], t_info *info);
pid_t				xfork(t_info *info);
void				*xmalloc(size_t size, t_info *info);
#endif