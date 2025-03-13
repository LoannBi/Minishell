/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** env_free
*/

#include <stdlib.h>
#include "minishell.h"


static void free_env_array(shell_t *shell)
{
    int i = 0;

    if (!shell->env_array)
        return;
    while (i < shell->env_size) {
        free(shell->env_array[i]);
        i++;
    }
    free(shell->env_array);
}

static void free_cmd_args(char **cmd_args)
{
    int i = 0;

    if (!cmd_args)
        return;
    while (cmd_args[i]) {
        free(cmd_args[i]);
        i++;
    }
    free(cmd_args);
}

void free_shell(shell_t *shell)
{
    if (!shell)
        return;
    free_env_array(shell);
    free_cmd_args(shell->cmd_args);
    if (shell->cmd_name)
        free(shell->cmd_name);
    if (shell->path)
        free(shell->path);
    free(shell);
}
