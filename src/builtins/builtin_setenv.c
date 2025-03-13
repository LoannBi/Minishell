/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** builtin_setenv
*/

#include "minishell.h"
#include "my.h"

static int handle_setenv_errors(shell_t *shell, char **args)
{
    if (args[2] && args[3]) {
        my_putstr("setenv: Too many arguments.\n");
        return 84;
    }
    if (!is_valid_env_name(args[1])) {
        my_putstr("setenv: Variable name must contain alphanumeric characters."
        "\n");
        shell->exit_status = 1;
        return 1;
    }
    return 0;
}

static int print_environment(shell_t *shell)
{
    for (int i = 0; shell->env_array[i]; i++) {
        my_putstr(shell->env_array[i]);
        my_putchar('\n');
    }
    return 0;
}

int builtin_setenv(shell_t *shell, char **args)
{
    if (!shell || !args || !args[0])
        return 84;
    if (!args[1])
        return print_environment(shell);
    if (handle_setenv_errors(shell, args) != 0)
        return 84;
    set_env_value(shell, args[1], args[2] ? args[2] : "");
    return 0;
}
