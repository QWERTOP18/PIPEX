/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:38:23 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 16:29:53 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "system.h"

void	build(int argc, char **argv, t_info *info)
{
	t_ast	*tree;

	argv[argc - 1] = NULL;
	tree = ast_new(&argv[2]);
	printf("Abstract Syntax Tree:\n");
	print_ast(tree, 0);
	printf("\nExecuting command pipeline:\n");
	exec_pipe(tree, info->fd_in, info->fd_out, info); // 最初は標準入力を渡さない
	system_exit(info, 0);                             // 正常終了したら終了する
}

int	main(int argc, char **argv, char **env)
{
	t_info	*info;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: %s <input> <command> <command> ... <output>\n", 2);
		return (1);
	}
	printf("main\n");
	printf("main\n");
	info = system_init(env);
	printf("%s\n", env[0]);
	if (ft_strncmp(argv[1], "heredoc", ft_strlen(argv[1]) == 0))
	{
		info->fd_in = open(HEREDOC, O_RDWR | O_TRUNC | O_CREAT, 0666);
		info->fd_out = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT,
				0666);
	}
	else
	{
		info->fd_in = open(argv[1], O_RDONLY);
		info->fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	}
	build(argc, argv, info);
	system_exit(info, 0);
	return (0);
}
