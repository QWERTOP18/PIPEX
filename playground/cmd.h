

#ifndef CMD_H
# define CMD_H

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_cmd
{
    char    *path;
    char    **args;
    pid_t pid;
    t_cmd   *next;
}                t_cmd;
#endif