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


t_ast *astnew_node(int type, t_ast *left, t_ast *right)
{
	t_ast    *new_node;

    new_node = ft_calloc(1, sizeof(t_ast));
    new_node->type = type;
    new_node->left = left;
    new_node->right = right;
    return (new_node);
}

t_ast	*astnew_node_cmd(char *argv)
{
	t_ast	*new_node;
	new_node = ft_calloc(1, sizeof(t_ast));
	new_node->type = TOKEN_CMD;
	new_node->argv = argv;
	return (new_node);
}

t_ast	*pipe(char **argv)
{
	t_ast	*new_node = astnew_node_cmd(*argv++);
	while(*argv != NULL)
	{
		new_node = astnew_node(TOKEN_PIPE,new_node,astnew_node_cmd(*argv++));
	}
	
	return (new_node);
}

t_btree	*ast_new_eof(char *arg, t_btree *left, t_btree *right)
{
	t_btree	*new_node;

	new_node = ft_btree_new(NULL);
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
	const char	*argv[] = {"infile", "ls -l", "cat", "out"};
	t_info	*info;
	

	
	info = system_init(NULL);

	return (0);
}
#endif