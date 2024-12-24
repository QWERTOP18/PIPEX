#!/bin/bash
# cc -Wall -Wextra -Werror *.c libft.a
cc -Wall -Wextra -Werror *.c libft.a

# ./a.out main.c /bin/cat /bin/cat out

# <infile yes | head -n 5 
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  --track-fds=yes -q ./a.out "infile" "ls -l" "cat -e" "grep a" "out"