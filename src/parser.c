#include "pipex.h"

t_node *ast_node_new(int token_type, void * val, t_info *info)
{
    //t_node *new_node = xmalloc(sizeof(t_node),info);
    t_node *new_node = malloc(sizeof(t_node));
    new_node->e_type = token_type;
    
    if (token_type == TOKEN_PIPE)
    {
        new_node->u_val.pipefds[0] = -1;
        new_node->u_val.pipefds[1] = -1;
    }
    else if (token_type == TOKEN_CMD || token_type >> REDIRECT & 1)
    {
        new_node->u_val.argv = ft_split((char *)val, ' ');
    }
    else if (token_type >> REDIRECT & 1)
    {
        new_node->u_val.file = (char *)val;
    }
    else if(token_type == TOKEN_EOF)
    {
        new_node->u_val.argv = NULL;
    }
    return new_node;
}



#define TEST_PARSE 1
#if TEST_PARSE

//EOF=>PIPE=>REDIRECT=>CMDの順番になるようにする
int main() {
    char **argv = {"infile", "ls -l", "cat", "out"};
    t_info *info = system_init(NULL);

    t_node *node_root = ast_node_new(TOKEN_EOF, NULL,info);
    t_node *node_in = ast_node_new(TOKEN_REDIR_IN,argv[0],info);
    t_node *node1 = ast_node_new(TOKEN_CMD,argv[1],info);
    t_node *node2 = ast_node_new(TOKEN_CMD,argv[2],info);
    t_node *node_out = ast_node_new(TOKEN_REDIR_OUT,argv[3],info);
    t_node *node_pipe = ast_node_new(TOKEN_PIPE,NULL,info);
    
    t_btree *ast_root = ft_btree_create_node(node_root);
    

    
    return 0;
}
#endif