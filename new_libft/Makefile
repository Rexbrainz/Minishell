# **************************************************************************** #
#                                    LIBFT                                     #
# **************************************************************************** #

NAME = libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC = 	ft_strmapi.c	ft_memset.c		ft_strlen.c\
		ft_putchar_fd.c	ft_atoi.c		ft_putendl_fd.c\
		ft_strncmp.c	ft_bzero.c		ft_putnbr_fd.c\
		ft_strnstr.c	ft_calloc.c		ft_putstr_fd.c\
		ft_strrchr.c	ft_isalnum.c	ft_split.c\
		ft_strtrim.c	ft_isalpha.c	ft_striteri.c\
		ft_strchr.c		ft_substr.c		ft_isascii.c\
		ft_strdup.c		ft_tolower.c	ft_isdigit.c\
		ft_memchr.c		ft_toupper.c	ft_isprint.c\
		ft_isspace.c\
		ft_memcmp.c		ft_strjoin.c	ft_itoa.c\
		ft_memcpy.c		ft_strlcat.c	ft_memmove.c\
		ft_strlcpy.c 	ft_printf.c 	print_char.c\
	   	print_int.c 	print_string.c 	print_unsigned_int.c\
	   	print_pointer.c print_hexl.c 	print_hexu.c\
		get_next_line.c get_next_line_bonus.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

# Bonus source files
BONUS_SRC = ft_lstadd_back.c	ft_lstiter.c	ft_lstnew.c\
			ft_lstsize.c		ft_lstlast.c	ft_lstclear.c\
			ft_lstadd_front.c	ft_lstdelone.c	ft_lstmap.c
			
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Commands
all: $(NAME)

# Create the static library
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Bonus target
bonus: $(BONUS_OBJ)
	@ar rcs $(NAME) $(BONUS_OBJ)

# Clean object files
clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

# Clean object files and the library
fclean: clean
	@rm -f $(NAME)

# Recompile everything
re: fclean all

# PHONY to avoid confusion
.PHONY: all clean fclean re bonus

