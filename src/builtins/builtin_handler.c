/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** builtin_handler
*/

#include "minishell.h"
#include "my.h"

static int handle_env_builtins(shell_t *shell, char **args)
{
    if (my_strcmp(args[0], "setenv") == 0) {
        builtin_setenv(shell, args);
        free_word_array(args);
        return 1;
    }
    if (my_strcmp(args[0], "unsetenv") == 0) {
        builtin_unsetenv(shell, args);
        free_word_array(args);
        return 1;
    }
    return 0;
}

static int handle_other_builtins(shell_t *shell, char **args)
{
    if (my_strcmp(args[0], "cd") == 0) {
        builtin_cd(shell, args);
        free_word_array(args);
        return 1;
    }
    if (my_strcmp(args[0], "echo") == 0) {
        builtin_echo(shell, args);
        free_word_array(args);
        return 1;
    }
    return 0;
}

int handle_builtins(shell_t *shell, char **args)
{
    if (handle_env_builtins(shell, args))
        return 1;
    if (handle_other_builtins(shell, args))
        return 1;
    return 0;
}
