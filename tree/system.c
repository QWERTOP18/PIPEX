#include "ft_system.h"


#include <string.h>//debug
void ft_system_exit(t_info *info,int status)
{
    // void astclear(void *data)
    // {
    //     free(data);
    // }
    strs_free(info->env_path);
   // ft_btreeclear(info->root, ast_clear);
    exit(status);
}

t_info *system_init(char **env)
{
    t_info *info = malloc(sizeof(t_info));
    if(!info)
        exit(E_ALLOCATE);
    memset(info,0,sizeof(t_info));
    info->root = ft_btreenew();
    while (env && *env)
    {
        if (strncmp(*env,"PATH=",strlen("PATH="))==0)
        {
            *env += strlen("PATH=");
            if (*env)
            {
                info->env_path = xsplit(env,' ',info);
            }
        }
        env++;
    }
    if (!info->env_path)
        info->env_path = xstrdup("",info);

    return info;
}