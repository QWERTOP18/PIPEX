#include "system.h"


void prefix_dispatcher(t_btree *current_node)
{
    const t_node *item = current_node->item;
    if (item->e_type ==TOKEN_PIPE)
    {
        setup_pipe(item->u_val.pipefds);
    }
    if (item->e_type == TOKEN_REDIRECT)
    {
        process_redirect_node(item->u_val.args);
    }
}

void suffix_dispatcher(t_btree *current_node)
{
    const t_node *item = current_node->item;
    if (item->e_type ==TOKEN_PIPE)
    {
        cleanup_pipe(item->u_val.pipefds);
    }
    if (item->e_type ==TOKEN_CMD)
    {
        process_cmd_node(item->u_val.args);
    }
}

int infix_dispatcher(t_btree *current_node, t_status status)
{
  const t_node *item = current_node->item;
  if (item->e_type ==TOKEN_EOF)
  {
    return 1;
  }

  return 0;
}
  