/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** env_set
*/

#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "my.h"

static int update_existing_env_var(shell_t *shell, const char *var,
    char *new_var, int len)
{
    int i = 0;

    while (i < shell->env_size) {
        if (my_strncmp(shell->env_array[i], var, len) == 0 &&
            shell->env_array[i][len] == '=') {
            free(shell->env_array[i]);
            shell->env_array[i] = new_var;
            return 1;
        }
        i++;
    }
    return 0;
}

static int add_new_env_var(shell_t *shell, char *new_var)
{
    size_t old_size = sizeof(char *) * shell->env_size;
    size_t new_size = sizeof(char *) * (shell->env_size + 2);
    char **new_env_array = my_realloc(shell->env_array, old_size, new_size);

    if (!new_env_array) {
        free(new_var);
        return 84;
    }
    shell->env_array = new_env_array;
    shell->env_array[shell->env_size] = new_var;
    shell->env_array[shell->env_size + 1] = NULL;
    shell->env_size++;
    return 0;
}

void set_env_value(shell_t *shell, const char *var, const char *value)
{
    char *new_var;
    int len;

    if (!shell || !var || !value)
        return;
    len = my_strlen(var);
    new_var = malloc(len + my_strlen(value) + 2);
    if (!new_var)
        return;
    my_strcpy(new_var, var);
    my_strcat(new_var, "=");
    my_strcat(new_var, value);
    if (update_existing_env_var(shell, var, new_var, len))
        return;
    add_new_env_var(shell, new_var);
}
