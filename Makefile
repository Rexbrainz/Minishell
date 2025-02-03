# NAME := minishell
# .DEFAULT_GOAL := all
# CC := cc
# RM := rm -rf

# ################################################################################
# ###############                  DIRECTORIES                      ##############
# ################################################################################

# OBJ_DIR := _obj
# LIBFT_PATH := new_libft
# LIBFT := $(LIBFT_PATH)/libft.a
# INC_DIRS := Includes $(LIBFT)
# SRC_DIRS := src
# EXECUTOR_PATH := $(SRC_DIRS)/executor
# EXECUTOR := $(EXECUTOR_PATH)/execution
# PARSER_PATH := $(SRC_DIRS)/parser
# PARSER := $(PARSER_PATH)/parsing

# vpath %.h $(INC_DIRS)
# vpath %.c $(SRC_DIRS)

# ################################################################################
# ###############                  SOURCE FILES                     ##############
# ################################################################################

# SRC_FILES := main.c

# SRC := $(addprefix src/, $(SRC_FILES))
# # SRC := $(addprefix src/, $(MAIN) $(LIST_LIST) $(PARSER))

# ################################################################################
# ###############               OBJECT FILES & RULES                ##############
# ################################################################################

# OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

# # Compilation flags and linking options
# CFLAGS := -Wall -Wextra -Werror -g -IIncludes -Ilibft -MMD -MP $(addprefix -I, $(INC_DIRS))
# LDFLAGS := -Llibft -lft
# CFLAGS_SAN := $(CFLAGS) -fsanitize=address -g
# LDFLAGS_SAN := $(LDFLAGS) -fsanitize=address

# # Submodule initialization rule
# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_PATH)

# # Default target to build
# all: $(NAME)

# # Build push_swap with libft and object files
# $(NAME): $(LIBFT) $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) -lreadline
# 	@echo "\033[0;32mSuccessful Compilation of $(NAME)\033[0m"

# # Compile source files into object files
# $(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
# 	mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Create the object directory if not exist
# $(OBJ_DIR):
# 	mkdir -p $(OBJ_DIR)

# # Clean up object files and libft
# clean:
# 	$(RM) $(OBJ_DIR)
# 	$(MAKE) clean -C $(LIBFT_PATH)

# # Clean up everything (object files and binaries)
# fclean: clean
# 	$(RM) $(NAME)
# 	$(MAKE) fclean -C $(LIBFT_PATH)

# # Rebuild everything (clean + all)
# re: fclean all

# # Build with sanitizers
# san: fclean
# 	$(MAKE) C

# -include $(OBJS:%.o=%.d)

# .PHONY: all clean fclean re bonus san

NAME := minishell
.DEFAULT_GOAL := all
CC := cc
RM := rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR := _obj
LIBFT_PATH := new_libft
LIBFT := $(LIBFT_PATH)/libft.a
GARBAGE_PATH := garbage_collector
GARBAGE := $(GARBAGE_PATH)/libgarbage.a
INC_DIRS := Includes $(LIBFT_PATH) $(GARBAGE_PATH) src/executor src/parser src/parser/scanner src/parser/parser
SRC_DIRS := src

vpath %.h $(INC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRC := $(shell find src -name '*.c')

################################################################################
###############               OBJECT FILES & RULES                ##############
################################################################################

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

# Compilation flags and linking options
CFLAGS := -Wall -Wextra -Werror -g $(addprefix -I, $(INC_DIRS)) -MMD -MP
LDFLAGS := -L$(LIBFT_PATH) -lft -L$(GARBAGE_PATH) -lgarbage -lreadline

# Submodule build rules
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(GARBAGE):
	$(MAKE) -C $(GARBAGE_PATH)

# Main build target
all: $(NAME)

$(NAME): $(LIBFT) $(GARBAGE) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "\033[0;32m$(NAME) compiled successfully!\033[0m"

# Object file compilation
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean targets
clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(GARBAGE_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(GARBAGE_PATH) fclean

re: fclean all

-include $(OBJS:%.o=%.d)

.PHONY: all clean fclean re