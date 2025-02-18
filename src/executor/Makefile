# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Source files and object files
SRC = exec_check_token.c exec_rec_exec.c exec_redirection.c \
      exec_run_cmd.c exec_table_builtin.c exec_track_path.c \
      exec_ultimate_error.c exec_rec_utility.c exec_run_utility.c \
	  exec_table_builtinfts.c exec_env_lita.c exec_table_exit.c
OBJ = $(SRC:.c=.o)

# Name of the executable
NAME = execution

# # Libft directory and library
# LIBFT_DIR = libft
# LIBFT = $(LIBFT_DIR)/libft.a

# Valgrind command for testing
# VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
# $(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
# $(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# test: $(NAME)
# 	./$(NAME) arg1 arg2

# valgrind: $(NAME)
# 	$(VALGRIND) ./$(NAME) arg1 arg2

.PHONY: all clean fclean re
