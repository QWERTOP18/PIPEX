#ifndef TREE_H
#define TREE_H
typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

typedef struct s_node
{
enum e_type
{
    TOKEN_CMD,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_PIPE,
    TOKEN_ARGS,
    TOKEN_EOF,
};

union u_val {
    char  *args;
    int    pipefds[2];
};
} t_node;
#endif