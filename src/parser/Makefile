#*************************************************************************************#
#                                   PARSING									  #
#*************************************************************************************#

# Program name
NAME = parser

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ../../new_libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC = main.c	scanner/init_tokens.c	parser.c\
  	  scanner/scanner_utils.c	scanner/scanner.c	scanner/add_lexemes.c\
	  scanner/add_lexemes1.c	scanner/add_lexemes2.c	scanner/scanner_utils1.c\
	  expand_variables.c	prompt_heredoc.c	rm_escape.c		join_cmds.c

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

# Clean object files and the program binary
fclean: clean
	@rm -f $(NAME)

# Rebuild the project
re: fclean all

# Specify dependencies
.PHONY: all clean fclean re

