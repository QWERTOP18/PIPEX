#include <stdio.h>
#include <stdlib.h>

// トークンタイプの定義
typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_PIPE,
    // 他のトークンタイプ
} TOKEN_TYPE;

// 共用体と型情報を含む構造体
typedef union u_item_value {
    TOKEN_TYPE token_type;
    char       *data;
    int        bracket_level;
} t_item_value;

typedef struct s_item {
    int type; // 現在有効なメンバーを識別する（例: 0=token_type, 1=data, 2=bracket_level）
    t_item_value value;
} t_item;

// 二分木ノード
typedef struct s_btree {
    struct s_btree *left;
    struct s_btree *right;
    void           *item;
} t_btree;

int main() {
    // ノードを作成
    t_btree *node = malloc(sizeof(t_btree));

    // item に格納するデータを作成
    t_item *data = malloc(sizeof(t_item));

    // `token_type` を設定
    data->type = 0;
    data->value.token_type = TOKEN_WORD;

    // ノードにデータを設定
    node->item = data;

    // データを取り出して使用
    t_item *retrieved_data = (t_item *)node->item;
    if (retrieved_data->type == 0) {
        printf("Token Type: %d\n", retrieved_data->value.token_type);
    } else if (retrieved_data->type == 1) {
        printf("Data: %s\n", retrieved_data->value.data);
    } else if (retrieved_data->type == 2) {
        printf("Bracket Level: %d\n", retrieved_data->value.bracket_level);
    }

    // メモリの解放
    free(data);
    free(node);

    return 0;
}
