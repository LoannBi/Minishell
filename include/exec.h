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
int handle_pipes(shell_t *shell, char *input);
int count_pipes(char *input);
int handle_line(shell_t *shell, char *input);
int prepare_execution(command_context_t *ctx);
int create_and_execute_process(command_context_t *ctx, char **args, int index);
int create_pipes(int pipe_count, int pipes[][2]);
void init_command_context(command_context_t *ctx, shell_t *shell, char *input);
int execute_pipeline(command_context_t *ctx);
int launch_commands(command_context_t *ctx);
#endif
