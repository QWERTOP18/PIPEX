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

} t_status;

// typedef struct s_temp
// {
//     char **argv;
//     int pipefds[2];
//     int openfds[2];
// } t_temp;
}				t_status;

typedef struct s_info
{
    t_status status;
    t_btree *root;
    char **env;
    char **env_path;
    int pipefds[2];
    //t_temp temp;
    //void (*__exit)(void *, int);
}t_info;


#define REDIRECT 4
#define OUT 1

typedef struct s_node {
    // t_type type;
    enum 
    {
        TOKEN_CMD,
        TOKEN_BUILDIN,
        TOKEN_PIPE,
        TOKEN_EOF,
        //TOKEN_ARGS,
        //TOKEN_REDIRECT,
        TOKEN_REDIR_IN = 0b10000,
        TOKEN_HEREDOC = 0b10001,
        TOKEN_REDIR_OUT = 0b10010,
        TOKEN_REDIR_APPEND = 0b10011,
    } e_type;
    union {
        char **argv;
        char *file;
        int pipefds[2];
    } u_val;
} t_node;
	t_status	status;
	t_btree		*root;
	char		**env;
	char		**env_path;
	// void		(*__exit)(void *, int);
	int			pipefds[2];
	t_pid_list	*pid_list;
}				t_info;


void system_exit(t_info *info,int status);
t_info *system_init(char **env);
#endif