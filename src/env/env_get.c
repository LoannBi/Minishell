/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** env_get
*/

#include "minishell.h"
#include "my.h"

char *get_env_value(shell_t *shell, const char *var)
{
    int len;
    int i = 0;

    if (!shell || !var)
        return NULL;
    len = my_strlen(var);
    while (i < shell->env_size) {
        if (my_strncmp(shell->env_array[i], var, len) == 0 &&
            shell->env_array[i][len] == '=') {
            return shell->env_array[i] + len + 1;
        }
        i++;
    }
    return NULL;
}
