/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:42:40 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 18:45:24 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AST_H
#define AST_H
#include <sys/types.h>
#include <unistd.h>
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





typedef struct s_pid_list
{
    pid_t pid;
    struct s_pid_list *next;
} t_pid_list;




#endif