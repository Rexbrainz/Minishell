NAME := minishell
.DEFAULT_GOAL := all
CC := cc
RM := rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR := _obj
LIBFT_PATH := libft
LIBFT := $(LIBFT_PATH)/libft.a
INC_DIRS := Includes $(LIBFT)
SRC_DIRS := src

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRC_FILES := main.c

SRC := $(addprefix src/, $(SRC_FILES))
# SRC := $(addprefix src/, $(MAIN) $(LIST_LIST) $(PARSER))

################################################################################
###############               OBJECT FILES & RULES                ##############
################################################################################

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

# Compilation flags and linking options
CFLAGS := -Wall -Wextra -Werror -g -IIncludes -Ilibft -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS := -Llibft -lft
CFLAGS_SAN := $(CFLAGS) -fsanitize=address -g
LDFLAGS_SAN := $(LDFLAGS) -fsanitize=address

# Submodule initialization rule
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

# Default target to build
all: $(NAME)

# Build push_swap with libft and object files
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "\033[0;32mSuccessful Compilation of $(NAME)\033[0m"

# Build checker with libft and object files
bonus: 

# Compile source files into object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the object directory if not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up object files and libft
clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_PATH)

# Clean up everything (object files and binaries)
fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)

# Rebuild everything (clean + all)
re: fclean all

# Build with sanitizers
san: fclean
	$(MAKE) C

-include $(OBJS:%.o=%.d)
# -include $(BONUS_OBJS:%.o=%.d)
# -include $(GNL_OBJS:%.o=%.d)

.PHONY: all clean fclean re bonus san