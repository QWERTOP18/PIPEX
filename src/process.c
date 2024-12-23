/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:42 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 14:39:42 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

// int ast_traverse_dispather

/*
 * CMDの処理はpreでもinでもどこでも大丈夫
 */
t_status	traverse_ast_nodes(t_btree *current_node, t_info *info)
{
	if (current_node == NULL)
		return (0);
	// プリフィックス処理
	prefix_dispatcher(current_node, info); // pipeの準備
	// 左部分木を処理
	traverse_ast_nodes(current_node->left, info);
	// インフィックス処理
	if (infix_dispatcher(current_node, info))
		return (info->status); //&&, || などの処理 redirectが失敗したら右に行かないようにする
	// 右部分木を処理
	traverse_ast_nodes(current_node->right, info);
	// サフィックス処理
	suffix_dispatcher(current_node, info); // pipeのクローズなど
	return (info->status);
}

// t_status ast_traverse(t_btree *root, t_info *info, int pipefds[])
// {
//     if (!root)
//         return (0);
//     if (info->status ==E_FATAL)
//         return (1);
//     t_node *node = root->item;
//     if (node->e_type == TOKEN_EOF)
//     {
//         ast_traverse(root->left, info, NULL);//ANY
//         return ;
//     }
//    else if (node->e_type == TOKEN_CMD)
//     {
//         // 実行する
//         ast_traverse(root->left,info, pipefds);//FILEIN
//         ast_traverse(root->right, info, pipefds);//FILEOUT
//         consume_cmd(node->u_val.args, info);
//     }
//     else if (node->e_type == TOKEN_PIPE)
//     {
//        consume_pipe(root,pipefds,info);//
//     }
//     else if (node->e_type == TOKEN_FILEIN)
//     {
//         consume_filein(node->u_val.args, info);
//     }
//     else if (node->e_type == TOKEN_FILEOUT)
//     {
//         consume_fileout(node->u_val.args, info);
//     }
//     return (0);
// }