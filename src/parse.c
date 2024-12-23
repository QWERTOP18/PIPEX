/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:32 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 20:03:57 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "system.h"
t_item	*ast_item_new(int token_type, void *val, t_info *info)
{
	t_item	*new_item;

	// t_item *new_item = xmalloc(sizeof(t_item),info);
	new_item = malloc(sizeof(t_item));
	new_item->e_type = token_type;
	if (token_type == TOKEN_PIPE)
	{
		new_item->u_val.pipefds[0] = -1;
		new_item->u_val.pipefds[1] = -1;
	}
	else if (token_type == TOKEN_CMD)
	{
		new_item->u_val.argv = ft_split((char *)val, ' ');
	}
	else if (token_type >> REDIRECT & 1)
	{
		new_item->u_val.file = (char *)val;
	}
	// else if (token_type == TOKEN_EOF)
	// {
	// 	new_item->u_val.argv = NULL;
	// }
	return (new_item);
}

t_btree	*ast_node_cmd_new(char *arg)
{
	t_btree	*new_node;

	new_node = ft_btree_new(item);
	return (new_node);
}

t_btree	*ast_node_pipe_new(char *arg, t_btree *left, t_btree *right)
{
	t_btree	*new_node;

	new_node = ft_btree_new(item);
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_btree	*ast_node_eof_new(char *arg, t_btree *left, t_btree *right)
{
	t_btree	*new_node;

	new_node = ft_btree_new(item);
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_btree	*parse_command_line(int argc, char **argv, t_info *info)
{
	t_btree	*root;

	root = ast_node_new(TOKEN_EOF, NULL, NULL);
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