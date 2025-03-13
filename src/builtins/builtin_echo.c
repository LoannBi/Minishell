/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** builtin_echo
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void print_env_variable(shell_t *shell, char *var)
{
    char *value = get_env_value(shell, var + 1);

    if (!value) {
        my_putstr(var + 1);
        my_putstr(": Undefined variable.\n");
        shell->exit_status = 1;
        return;
    }
    my_putstr(value);
    my_putstr("\n");
    shell->exit_status = 0;
}

static void print_args(char **args)
{
    int i = 1;

    while (args[i]) {
        if (i > 1)
            my_putstr(" ");
        my_putstr(args[i]);
        i++;
    }
    my_putstr("\n");
}

void builtin_echo(shell_t *shell, char **args)
{
    if (!args[1]) {
        my_putstr("\n");
        shell->exit_status = 0;
        return;
    }
    if (args[1][0] == '$') {
        print_env_variable(shell, args[1]);
        return;
    }
    print_args(args);
    shell->exit_status = 0;
}
