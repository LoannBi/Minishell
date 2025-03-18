##
## EPITECH PROJECT, 2024
## My_top_prject
## File description:
## Makefile
##

SRC_DIR = src
LIB_DIR = lib

SRC =	src/env/env_free.c									\
		src/env/env_init.c									\
		src/env/env_get.c									\
		src/env/env_set.c									\
		src/builtins/builtin_setenv.c						\
		src/env/env_unset.c									\
		src/builtins/builtin_unsetenv.c						\
		src/exec/exec_command.c								\
		src/exec/path_handling.c							\
		src/builtins/builtin_cd.c							\
		src/builtins/builtin_echo.c							\
		src/exec/command_handler.c							\
		src/exec/pipe_handler.c								\
		src/exec/pip_exec.c									\
		src/exec/pip_init.c									\
		src/exec/pip_wait.c									\
		src/utils/array_utils.c								\
		src/utils/str_utils.c								\
		src/utils/error_handling.c							\
		src/builtins/builtin_handler.c						\
		src/main.c											\
		src/utils/line_handlers.c							\

LIB = 	lib/my_atoi.c					\
		lib/my_put_nbr.c				\
		lib/my_putchar.c				\
		lib/my_putstr.c					\
		lib/my_strcat.c					\
		lib/my_strcmp.c					\
		lib/my_strlen.c					\
		lib/my_strcpy.c					\
		lib/my_strdup.c					\
		lib/my_strndup.c				\
		lib/my_strchr.c					\
		lib/my_swap.c					\
		lib/my_realloc.c				\
		lib/my_strncmp.c				\
		lib/str_to_word_array.c			\

SRC_OBJ = $(SRC:.c=.o)
LIB_OBJ = $(LIB:.c=.o)
OBJ = $(SRC_OBJ) $(LIB_OBJ)

NAME = mysh

CFLAGS += -I./include -Wall -Wextra -g
LDFLAGS += -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "Binary $(NAME) created."

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc $(CFLAGS) -c $< -o $@

$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "Binary $(NAME) removed."

re: fclean all

tests_run: fclean
	@if [ -d "gcovr" ]; then rm -rf gcovr; fi
	@mkdir gcovr
	@echo "Compiling tests..."
	@gcc -O0 -o unit_tests \
		$(filter-out src/animate.c, $(SRC)) $(TESTS) \
		-I include -lcriterion -fprofile-arcs -ftest-coverage \
		-Wall -Wextra

	@echo "Executing tests..."
	@./unit_tests || true
	@echo "Generate coverage reports..."
	@gcovr --exclude tests/ || exit 1
	@gcovr --exclude tests/ --branches || exit 1
	@gcovr --exclude tests/ --html-details gcovr/coverage.html || exit 1
	@gcovr --exclude tests/ --txt gcovr/coverage_summary.txt || exit 1
	@rm -f unit_tests
