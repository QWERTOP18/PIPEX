/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:32 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 13:08:38 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_node	*ast_node_new(int token_type, void *val, t_info *info)
{
	t_node	*new_node;

	// t_node *new_node = xmalloc(sizeof(t_node),info);
	new_node = malloc(sizeof(t_node));
	new_node->e_type = token_type;
	if (token_type == TOKEN_PIPE)
	{
		new_node->u_val.pipefds[0] = -1;
		new_node->u_val.pipefds[1] = -1;
	}
	else if (token_type == TOKEN_CMD)
	{
		new_node->u_val.argv = ft_split((char *)val, ' ');
	}
	else if (token_type >> REDIRECT & 1)
	{
		new_node->u_val.file = (char *)val;
	}
	// else if (token_type == TOKEN_EOF)
	// {
	// 	new_node->u_val.argv = NULL;
	// }
	return (new_node);
}

#define TEST_PARSE 1
#if TEST_PARSE

// EOF=>PIPE=>REDIRECT=>CMDの順番になるようにする
int	main(void)
{
	char	**argv;
	t_info	*info;
	t_node	*node_root;
	t_node	*node_in;
	t_node	*node1;
	t_node	*node2;
	t_node	*node_out;
	t_node	*node_pipe;
	t_btree	*ast_root;

	argv = {"infile", "ls -l", "cat", "out"};
	info = system_init(NULL);
	node_root = ast_node_new(TOKEN_EOF, NULL, info);
	node_in = ast_node_new(TOKEN_REDIR_IN, argv[0], info);
	node1 = ast_node_new(TOKEN_CMD, argv[1], info);
	node2 = ast_node_new(TOKEN_CMD, argv[2], info);
	node_out = ast_node_new(TOKEN_REDIR_OUT, argv[3], info);
	node_pipe = ast_node_new(TOKEN_PIPE, NULL, info);
	ast_root = ft_btree_create_node(node_root);
	return (0);
}
#endif