#*************************************************************************************#
#                                   PARSING									  #
#*************************************************************************************#

# Program name
NAME = parsing

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ../../new_libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC = main.c	scanner/init_tokens.c	parser/parser.c\
  	  scanner/scanner_utils.c	scanner/scanner.c	scanner/add_lexemes.c\
	  scanner/add_lexemes1.c	scanner/add_lexemes2.c	scanner/scanner_utils1.c\
	  parser/expand_variables.c		parser/prompt_heredoc.c		parser/rm_escape.c\
	  parser/join_cmds.c	  parser/organize_file.c	parser/free_tokens_list.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Build the program
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Clean object files and the program binary
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild the project
re: fclean all

# Specify dependencies
.PHONY: all clean fclean re

