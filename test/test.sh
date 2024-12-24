#!/bin/bash
# cc -Wall -Wextra -Werror *.c libft.a
cc -Wall -Wextra -Werror *.c libft.a

# ./a.out main.c /bin/cat /bin/cat out

# <infile yes | head -n 5 
valgrind --leak-check=full --show-leak-kinds=all ./a.out "infile" "cat" "cat" "out"