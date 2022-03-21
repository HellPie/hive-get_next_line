# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 19:46:05 by drossi            #+#    #+#              #
#    Updated: 2022/03/21 19:15:54 by drossi           ###   ########.fr        #
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
	$(info Running Norminette ($(shell python3 -m norminette -v)) compliance tests)
	@python3 -m norminette $(wildcard $(GNL_INC_DIR)/*.h) $(GNL_SRC) | grep "Error\|Warn"; exit 0

symbols: CFLAGS += -fPIC
symbols: $(LFT_OBJ) $(GNL_OBJ)
	$(info Verifying usage of undefined (external) symbols)
	@rm -f $(OBJ_DIR)/out.o
	@$(CC) -Wl,--whole-archive $(LFT_OBJ) -Wl,--no-whole-archive -shared $(GNL_OBJ) -o $(OBJ_DIR)/out.o
	@nm -uP $(OBJ_DIR)/out.o | grep -w "U"
	@rm -f $(OBJ_DIR)/out.o $(LFT_OBJ) $(GNL_OBJ)

ifeq ($(shell uname -s),Linux)
test: symbols
endif

test: debug norme
	$(info Running tests for $(NAME))
	@ASAN_OPTIONS=abort_on_error=1:fast_unwind_on_malloc=1:detect_leaks=1 UBSAN_OPTIONS=print_stacktrace=1 G_SLICE=always-malloc G_DEBUG=gc-friendly ./$(NAME) --color --timed --verbose; exit 0
	@$(MAKE) fclean > /dev/null

clean:
	$(info Removing all objects, $(GNL_OBJ_DIR) and $(OBJ_DIR) if they exists)
	@$(MAKE) -C $(LFT_LIB_DIR) clean > /dev/null
	@rm -rf $(GNL_OBJ_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	$(info Removing $(NAME) if it exists)
	@$(MAKE) -C $(LFT_LIB_DIR) fclean > /dev/null
	@rm -f $(NAME)

re: fclean all

.PHONY: debug norme symbols test all clean fclean re
