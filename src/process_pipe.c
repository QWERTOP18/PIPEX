
#include "pipex.h"


void setup_pipe(int pipefds[],t_info *info)
{
    if(pipe(pipefds))
    {
        perror("pipe");
        system_exit(info, errno);
    }
    info->pipefds[0] = pipefds[0];
    info->pipefds[1] = pipefds[1];
}
void cleanup_pipe(int pipefds[],t_info *info)
{
    // Close the write end of the pipe
    xclose(&pipefds[1]);
    xclose(&pipefds[2]);
}