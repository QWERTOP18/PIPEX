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
#define HEREDOC "THIS_FILE_SAHLLNOT_EXIST"
# ifndef PATH_MAX
#  define PATH_MAX = 1024
# endif
typedef enum e_status
{
	E_NONE,
	E_FATAL,
	E_ALLOCATE,

} t_status;


typedef struct s_info
{
    t_status status;
    t_ast *root;
    char **env;
    char **env_path;
    int fd_in;
    int fd_out;
}t_info;

void system_exit(t_info *info,int status);
t_info *system_init(char **env);

int	fetch_absolutepath(char path[], char *src, char **env_path, int mode);
#endif