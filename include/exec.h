/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** exec
*/

#include "minishell.h"
#include "my.h"

#ifndef INCLUDED_EXEC_H
    #define INCLUDED_EXEC_H

int execute_command(shell_t *shell, char *cmd_path, char **args);
char *find_executable(shell_t *shell, char *cmd);

#endif
