#include <stdio.h>

typedef enum e_item_type {
    ITEM_TYPE_STRING,
    ITEM_TYPE_INT,
    ITEM_TYPE_FLOAT
} t_item_type;

typedef union u_item_value {
    char  *string_value;
    int    int_value;
    float  float_value;
} t_item_value;

typedef struct s_item {
    t_item_type type;  // 格納されているデータの型を保持
    t_item_value value; // 実際のデータ
} t_item;

int main() {
    t_item item;

    // int を格納
    item.type = ITEM_TYPE_INT;
    item.value.int_value = 42;

    // 値を取り出す
    if (item.type == ITEM_TYPE_INT) {
        printf("Integer: %d\n", item.value.int_value);
    }

    // string を格納
    item.type = ITEM_TYPE_STRING;
    item.value.string_value = "Hello, World!";

    // 値を取り出す
    if (item.type == ITEM_TYPE_STRING) {
        printf("String: %s\n", item.value.string_value);
    }

    return 0;
}
