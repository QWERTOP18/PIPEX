NAME = pipex

SRC = file_test.c execve.c
OBJ := $(SRC:%.c=%.o)

CC = cc
CCFLAGS = -Werror -Wall -Wextra

all: $(NAME)

libft:
	@make -C ../libft/

$(NAME): $(OBJ)
	@make -C ../libft
	$(CC) $^ -L../libft -lft -o $(NAME)

%.o: %.c
	$(CC) -Iincludes -I../libft -c $< -o $@
# 	$(CC) $(CCFLAGS) -Iincludes -Ilibft -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BON)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

debug: $(OBJ)
	$(CC) $(CCFLAGS) -fsanitize=address -Llibft -lft $^ -o $(NAME)

test: $(OBJ)
	./pipex "ls -l ../" "ls -l ../"

duptest: $(OBJ)
	./pipex read.txt write.txt

.PHONY: libft test
