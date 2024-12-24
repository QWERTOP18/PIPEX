NAME		:= pipex
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf
ROOT_DIR	:= .
OUT_DIR		:= $(ROOT_DIR)/obj
INCS_DIR	:= $(ROOT_DIR)/src
LIBFT_DIR	:= $(ROOT_DIR)/libft
LIBFT		:= $(LIBFT_DIR)/libft.a
IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)

SRC_FILES	:= ast.c exec.c main.c path.c system.c xunistd.c heredoc.c
SRCS		:= $(addprefix src/, $(SRC_FILES))

OBJS		:= $(addprefix $(OUT_DIR)/, $(SRC_FILES:.c=.o))
DEPS		:= $(OBJS:.o=.d)

ifeq ($(DEBUG), 1)
	CFLAGS	+= -g -fsanitize=address
else
	CFLAGS	+= -O2
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(LIBFT): | $(LIBFT_DIR)/Makefile
	$(MAKE) -C $(LIBFT_DIR)

$(OUT_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OUT_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

$(LIBFT_DIR)/Makefile:
	git submodule update --init --recursive

sub:
	git submodule update --remote

norm:
	@norminette $(SRCS) $(INCS_DIR)

debug:
	$(MAKE) DEBUG=1

case1: $(NAME)
	@$(ROOT_DIR)/$(NAME) "infile" "ls -l" "grep Make" "outfile"

case2: $(NAME)
	@$(ROOT_DIR)/$(NAME) "infile" "ls -l" "grep Make" "outfile"

case3: $(NAME)
	@$(ROOT_DIR)/$(NAME) "infile" "ls -l" "grep Make" "outfile"

case4: $(NAME)
	@$(ROOT_DIR)/$(NAME) "infile" "ls -l" "grep Make" "outfile"

.PHONY: all clean fclean re initsub sub norm debug

-include $(DEPS)
