/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normcheck.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 02:30:12 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/20 02:46:49 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMCHECK_H
# define NORMCHECK_H

typedef struct s_token
{
	enum
	{
		TT_EOF,
		TT_ERROR
	} e_type;
	char				*value;
}						t_token;
typedef struct s_ast_node
{
	enum
	{
		NT_CMD,
		NT_PIPE,
		NT_PRIORITY,
		NT_EOP,
	} e_type;
	union
	{
		t_list			*args;
		int				pipefds[2];
		int				priority_level;
		t_token_type	eop_type;
	} u_val;
}						t_ast_node_item;

#endif
