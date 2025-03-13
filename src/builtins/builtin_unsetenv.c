/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** builtin_unsetenv
*/

#include "minishell.h"
#include "my.h"

int builtin_unsetenv(shell_t *shell, char **args)
{
    if (!shell || !args || !args[0])
        return 84;
    if (!args[1]) {
        my_putstr("unsetenv: Too few arguments.\n");
        return 84;
    }
    if (args[2]) {
        my_putstr("unsetenv: Too many arguments.\n");
        return 84;
    }
    unset_env_value(shell, args[1]);
    return 0;
}
