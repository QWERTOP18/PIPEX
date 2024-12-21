
#include "system.h"



void setup_pipe(int pipefds[],t_info *info)
{
    if(pipe(pipefds))
    {
        perror("pipe");
        system_exit(info, errno);
    }
}
void cleanup_pipe(int pipefds[],t_info *info)
{
    // Close the write end of the pipe
    close(pipefds[1]);
    close(pipefds[2]);
}