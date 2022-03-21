# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 19:46:05 by drossi            #+#    #+#              #
#    Updated: 2022/03/21 21:01:56 by drossi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := gnl

# Directories
LFT_LIB_DIR := ../libft
LFT_INC_DIR := $(LFT_LIB_DIR)/include
GNL_INC_DIR := ..
GNL_SRC_DIR := ..
GNL_OBJ_DIR := ../build
INC_DIR := include
SRC_DIR := src
OBJ_DIR := build

# Sources and objects
LFT_INC := $(LFT_INC_DIR)
LFT_LIB := ft
LFT_OBJ := $(LFT_LIB_DIR)/lib$(LFT_LIB).a
GNL_INC := $(GNL_INC_DIR)
GNL_SRC := $(wildcard $(GNL_SRC_DIR)/*.c)
GNL_OBJ := $(patsubst $(GNL_SRC_DIR)/%.c,$(GNL_OBJ_DIR)/%.o,$(GNL_SRC))
INC := $(INC_DIR)
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Compiler flags and defaults
CC := clang
CFLAGS += -Wall -Werror -Wextra

# Norminette configuration
NORMINETTE ?= python3 -m norminette

ifeq ($(DEBUG),1)
	$(info Configuring additional debug options.)
	CFLAGS += -fsanitize=address,undefined -fno-sanitize-recover=all -g -DDEBUG
endif

# Build, archive and index the static library
$(NAME): $(OBJ) $(GNL_OBJ) $(LFT_OBJ)
	$(info Building $@ as it was new or changed)
	@$(CC) $(CFLAGS) -L$(LFT_LIB_DIR) -l$(LFT_LIB) -o $@ $^

# Build a single source file into its correspondent object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(info Building $@ from $< as it was new or changed)
	@mkdir -p $$(dirname $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(GNL_INC) -I$(LFT_INC) -c $< -o $@

# Build core dependencies into their correspondent object files
$(GNL_OBJ_DIR)/%.o: $(GNL_SRC_DIR)/%.c
	$(info Building $@ from $< as it was new or changed)
	@mkdir -p $$(dirname $@)
	@$(CC) $(CFLAGS) -I$(GNL_INC) -I$(LFT_INC) -c $< -o $@

$(LFT_OBJ):
	$(info Building $@ as it was new or changed)
	@$(MAKE) -C $(LFT_LIB_DIR) fclean > /dev/null
	@$(MAKE) CFLAGS="$(CFLAGS)" -C $(LFT_LIB_DIR) > /dev/null

# Other build rules, auxiliary target rules and cleanup rules
all: $(NAME)

debug:
	$(info Compiling $(NAME) with debug flags)
debug: CFLAGS += -fsanitize=address,undefined -fno-sanitize-recover=all -g -DDEBUG
debug: all

norme:
	$(info Running Norminette ($(shell $(NORMINETTE) -v)) compliance tests)
	@$(NORMINETTE) $(wildcard $(GNL_INC_DIR)/*.h) $(GNL_SRC) | grep "Error\|Warn"; exit 0

moulinette: $(LFT_OBJ)
	$(info Simulating build instructions like Moulinette according to GNL docs)
	@clang -I ../libft/include -I .. -Wall -Wextra -Werror -o get_next_line.o -c ../get_next_line.c
	@clang -I ../libft/include -I .. -Wall -Wextra -Werror -o main.o -c src/main.c
	@clang -o test_gnl main.o get_next_line.o -I ../libft/includes -L ../libft -lft
	@./test_gnl Makefile > /dev/null
	@$(RM) -r test_gnl main.o get_next_line.o

symbols: $(GNL_OBJ)
	$(info Verifying usage of undefined (external) symbols)
	@$(MAKE) -C $(LFT_LIB_DIR) symbols > /dev/null
	@ld -r $(GNL_OBJ) $(wildcard $(LFT_LIB_DIR)/build/**/*.o) -o packed.o
	@nm -uP packed.o | grep -w "U"
	@$(RM) $(OBJ_DIR)/packed.o; exit 0

test: moulinette debug norme symbols
	$(info Running tests for $(NAME))
	@ASAN_OPTIONS=abort_on_error=1:fast_unwind_on_malloc=1:detect_leaks=1 UBSAN_OPTIONS=print_stacktrace=1 G_SLICE=always-malloc G_DEBUG=gc-friendly ./$(NAME) --color --timed --verbose; exit 0
	@$(MAKE) fclean > /dev/null

clean:
	$(info Removing all objects, $(GNL_OBJ_DIR) and $(OBJ_DIR) if they exists)
	@$(MAKE) -C $(LFT_LIB_DIR) clean > /dev/null
	@$(RM) -r $(GNL_OBJ_DIR)
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	$(info Removing $(NAME) if it exists)
	@$(MAKE) -C $(LFT_LIB_DIR) fclean > /dev/null
	@$(RM) $(NAME)

re: fclean all

.PHONY: debug norme symbols moulinette test all clean fclean re
