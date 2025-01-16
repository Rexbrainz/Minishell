#*************************************************************************************#
#                                   PARSING									  #
#*************************************************************************************#

# Program name
NAME = parser

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC = main.c	parser.c	scanner.c
# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Build the program
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJ) -lreadline

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

