/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:25:08 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/05 03:51:33 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#define PATH 5
#define MAX_PATH 1024
#define MAX_CMD 1024
// #include "libft.h"

// debug
#include <stdlib.h>
#include <string.h>

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;
typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_PIPE,
	//further analtics
	TOKEN_FILE,
	TOKEN_PATH,
	TOKEN_ARG,
	TOKEN_CMD,
	TOKEN_FDIN,

    // TOKEN_STDIN,
    // TOKEN_STDOUT,
    // TOKEN_STDERR,
    // 他のトークンタイプ
} TOKEN_TYPE;

typedef enum e_item_type {
    TYPE,
	ITEM_PATH,
} t_item_type;

typedef union u_item_value {
    char  *string_value;
    int    fdin;
    char *file;
	char *path;
} t_item_value;

typedef struct s_item {
    t_item_type type;  // 格納されているデータの型を保持
    t_item_value value; // 実際のデータ
} t_item;

typedef struct s_cmd
{
	char path[PATH_MAX];
	char **args;

	//struct s_cmd *next;
} t_cmd;

int	fetch_absolute_path(char path[], char **env, int mode)
{
	static char path_val[MAX_PATH] = {0};


	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", PATH) == 0)
		{
			path = *env + PATH;
			return (ft_split(path, ':'));
		}
		env++;
	}
	
}

int w_absolute_path(char **env, char *path, int mode)
{
	if (path==NULL || env==NULL)
		return 1;
	if (path[0] == '/')
        return access(path, mode);
	//if (path[0] == '.') 相対パス
	
}


int w_parse(t_cmd *cmds[], char **argv, char **env)
{
	int i = 0;
	//strlcpy(cmds[0]->fdin, argv[0],MAX_PATH);
	while(argv[++i])
	{
		cmds[i]->args = xsplit(argv, ' ');
		//strlcpy(cmds[i]->path, cmds[i]->args[0], MAX_PATH);
	}
	//strlcpy(cmds[--i]->fdout, argv[--i],MAX_PATH);
	cmds[i] = NULL;
	return 0;
}

static char *av[] = {"ls", "-l", NULL};
int	main(int argc, char **argv, char **env)
{
	int fd_from;
	int fd_via;
	int fd_to;
	printf("%s\n\n", __DATE__);
	// if (argc < 5)
	// {
	// 	printf("Usage:./pipex file1 cmd1 cmd2 file2\n");
	// 	return (1);
	// }
	//char **absolute_path = fetch_absolute_path(env);
	t_cmd cmds[MAX_CMD];
	w_parse(&cmds, &argv[1], env);
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		printf("This is the child process!\n");
		printf("%d\n", execve("/bin/ls", av, env));
		perror("execv:");
	}
	else
	{
		// This block is executed by the parent process
		printf("This is the parent process. Child PID is: %d\n", pid);
		wait(NULL); // Parent waits for the child to finish
	}
	// to do make wrapper func of open
	// fd_from = open(argv[1], O_RDWR);
	// fd_to = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// if (fd_from == -1 || fd_to == -1)
	// {
	// 	perror("Error while opening files");
	// 	return (1);
	// }
	return (0);
}