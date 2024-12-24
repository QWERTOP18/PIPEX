/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:38:33 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 17:47:29 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("  ");
	if (node->type == TOKEN_CMD)
		printf("CMD: %s\n", node->args[0]);
	else if (node->type == TOKEN_PIPE)
		printf("PIPE\n");
	// 左側と右側のノードを表示
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

#ifdef PARSE
int	main(void)
{
	char	*commands[] = {"ls", "cat", "grep .c", "wc -l", NULL};
	t_ast	*tree;

	tree = pipe_tree(commands);
	printf("Abstract Syntax Tree:\n");
	print_ast(tree, 0);
	return (0);
}
#endif