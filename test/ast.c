/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:39:02 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 16:31:32 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

void	error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

t_ast	*astnew_node(int type, char *argv)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	new_node->type = type;
	new_node->args = NULL;
	(void)argv; // ft_split(argv, ' ');
	return (new_node);
}

t_ast	*ast_new(char **argv)
{
	t_ast	*root_node;
	t_ast	*current_node;

	printf("%s\n", __FUNCTION__);
	root_node = astnew_node(TOKEN_PIPE, NULL);
	current_node = root_node;
	while (*argv != NULL)
	{
		current_node->left = astnew_node(TOKEN_CMD, *argv++);
		if (*argv)
			current_node->right = astnew_node(TOKEN_PIPE, NULL);
		current_node = current_node->right;
	}
	return (root_node);
}
void	ast_clear(t_ast *node)
{
	if (!node)
		return ;
	ast_clear(node->left);
	ast_clear(node->right);
	if (node->args)
	{
		ft_strs_clear(node->args);
	}
	free(node);
}
