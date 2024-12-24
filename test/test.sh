#!/bin/bash
# cc -Wall -Wextra -Werror *.c libft.a
cc *.c libft.a && ./a.out "infile" "ls" "cat" "wc -l" "out"

# ./a.out main.c /bin/cat /bin/cat out

# <infile yes | head -n 5 