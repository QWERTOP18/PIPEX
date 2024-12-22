#include "pipex.h"


void prefix_dispatcher(t_btree *current_node,t_info *info)
{
    const t_node *item = current_node->item;
    if (item->e_type ==TOKEN_PIPE)
    {
        setup_pipe(item->u_val.pipefds, info);
    }
}

void suffix_dispatcher(t_btree *current_node,t_info *info)
{
    const t_node *item = current_node->item;
    if (item->e_type ==TOKEN_PIPE)
    {
        cleanup_pipe(item->u_val.pipefds,info);
    }
    if (item->e_type ==TOKEN_CMD)
    {
        process_cmd_node(item->u_val.argv,info);
    }
}

int infix_dispatcher(t_btree *current_node, t_info *info)
{
    const t_node *item = current_node->item;
    if (item->e_type ==TOKEN_EOF)
    {
        return 1;
    }
    if (item->e_type >> REDIRECT & 1)
    {
        return process_redir_node(item, info);
    }

    return 0;
}
  