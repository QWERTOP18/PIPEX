/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dispacher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:48 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 14:31:00 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "system.h"

void	prefix_dispatcher(t_btree *current_node, t_info *info)
{
	const t_node	*item = current_node->item;

	if (item->e_type == TOKEN_PIPE)
	{
		setup_pipe(item->u_val.pipefds, info);
	}
}

void	suffix_dispatcher(t_btree *current_node, t_info *info)
{
	const t_node	*item = current_node->item;

	if (item->e_type == TOKEN_PIPE)
	{
		cleanup_pipe(item->u_val.pipefds, info);
	}
	if (item->e_type == TOKEN_CMD)
	{
		process_cmd_node(item->u_val.argv, info);
	}
}

int	infix_dispatcher(t_btree *current_node, t_info *info)
{
	const t_node	*item = current_node->item;

	if (item->e_type == TOKEN_EOF)
	{
		return (1);
	}
	if (item->e_type >> REDIRECT & 1)
	{
		return (process_redir_node(item, info));
	}
	return (0);
}
