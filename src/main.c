/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:38:23 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/24 19:11:54 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "system.h"

void	build(char **argv, t_info *info)
{
	info->root = ast_new(argv, info);
	process_pipe(info->root, info->fd_in, info->fd_out, info);
    system_exit(info, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_info	*info;
    const char *outfile = argv[argc - 1];
    argv[argc - 1] = NULL;
    argv++;
	if (argc < 5)
	{
		ft_putstr_fd("Usage: %s <input> <command> <command> ... <output>\n", 2);
		return (1);
	}
	info = system_init(env);
	if (ft_strncmp(*argv, "heredoc", ft_strlen(*argv) == 0))
	{
		info->fd_out = xopen(outfile, O_WRONLY | O_APPEND | O_CREAT,0666);
        info->fd_in = heredoc(info, *++argv);
        build(++argv, info);
	}
    info->fd_in = xopen(*argv, O_RDONLY, 0);
	info->fd_out = xopen(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	build(++argv, info);
	
	return (0);
}
