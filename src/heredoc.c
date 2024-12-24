#include "system.h"

int heredoc(t_info *info, const char *delimiter)
{
    int pipefd[2];
    char *line;

    xpipe(pipefd, info);
    line = get_next_line(0);
    while (line)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 &&
            ft_strlen(line) == ft_strlen(delimiter) + 1)
            break;
        ft_putstr_fd(line, pipefd[1]);
        free(line);
        line = get_next_line(0);
    }
    xfree((void **)&line);
    xclose(&pipefd[1]);
    return pipefd[0];
}
