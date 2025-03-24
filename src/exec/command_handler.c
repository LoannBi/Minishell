/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** command_handler
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int handle_command_not_found(char **args, shell_t *shell)
{
    my_putstr(args[0]);
    my_putstr(": Command not found.\n");
    free_word_array(args);
    shell->exit_status = 1;
    return 1;
}

static int handle_exit_command(char **args, shell_t *shell)
{
    if (my_strcmp(args[0], "exit") != 0)
        return 0;
    free_word_array(args);
    free_shell(shell);
    exit(shell->exit_status);
}

static char **prepare_args(char *input)
{
    char *cleaned_input = clean_str(input);
    char **args;

    if (!cleaned_input || !cleaned_input[0]) {
        free(cleaned_input);
        return NULL;
    }
    args = my_str_to_word_array(cleaned_input, ' ');
    free(cleaned_input);
    return args;
}

static char *get_command_path(shell_t *shell, char *command)
{
    char *path = find_executable(shell, command);

    return path;
}

static int handle_special_cases(shell_t *shell, char *input, char **args)
{
    if (!args || !args[0]) {
        return 0;
    }
    if (unmatched_quotes(input)) {
        shell->exit_status = 1;
        return 1;
    }
    if (handle_exit_command(args, shell)) {
        return shell->exit_status;
    }
    if (handle_builtins(shell, args)) {
        return shell->exit_status;
    }
    return -1;
}

static int contains_pipe(char *input)
{
    for (int i = 0; input && input[i]; i++) {
        if (input[i] == '|')
            return 1;
    }
    return 0;
}

int handle_command(shell_t *shell, char *input)
{
    char **args;
    int special_case;
    char *cmd_path;

    if (has_redirection(input))
        return handle_redirections(shell, input);
    if (contains_pipe(input))
        return handle_pipes(shell, input);
    args = prepare_args(input);
    special_case = handle_special_cases(shell, input, args);
    if (special_case != -1)
        return special_case;
    cmd_path = get_command_path(shell, args[0]);
    if (!cmd_path)
        return handle_command_not_found(args, shell);
    shell->exit_status = execute_command(shell, cmd_path, args);
    free(cmd_path);
    free_word_array(args);
    return shell->exit_status;
}
