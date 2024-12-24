#!/bin/bash
# cc -Wall -Wextra -Werror *.c libft.a
cc -Wall -Wextra  *.c libft.a && ./a.out "infile" "ls" "wc" "out"

# ./a.out main.c /bin/cat /bin/cat out

# <infile yes | head -n 5 