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
typedef enum e_type
{
	TOKEN_CMD,
	TOKEN_BUILDIN,
	TOKEN_PIPE,
	TOKEN_EOF,
	TOKEN_REDIR_IN = 0b10000,
	TOKEN_HEREDOC = 0b10001,
	TOKEN_REDIR_OUT = 0b10010,
	TOKEN_REDIR_APPEND = 0b10011,
} t_type;



typedef struct s_ast {
    struct t_ast *left;
    struct t_ast *right;
	t_type type;
    char *argv;
} t_ast;



#endif