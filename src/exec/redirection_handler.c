/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** redirection_handler - Gestion des redirections d'entrée/sortie
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static int execute_with_redirection(shell_t *shell,
    char *command_part, char *file_part, redirection_type_t type)
{
    int old_stdout;
    int status;

    old_stdout = apply_redirection_out(file_part, type);
    if (old_stdout == -1) {
        free(command_part);
        free(file_part);
        return 1;
    }
    status = handle_command(shell, command_part);
    dup2(old_stdout, STDOUT_FILENO);
    close(old_stdout);
    free(command_part);
    free(file_part);
    return status;
}

int handle_redirection_out(shell_t *shell, char *input)
{
    char *command_part;
    char *file_part;
    redirection_type_t type;

    if (has_multiple_redirections(input)) {
        print_error("Ambiguous output redirect.\n");
        shell->exit_status = 1;
        return 1;
    }
    command_part = extract_command_part(input, &file_part, &type);
    if (check_redirection_syntax(command_part, file_part))
        return 1;
    return execute_with_redirection(shell, command_part, file_part, type);
}

static int handle_redirection_type(shell_t *shell, char *input)
{
    if (has_redirection_out(input))
        return handle_redirection_out(shell, input);
    return -1;
}

int handle_redirections(shell_t *shell, char *input)
{
    int result;

    result = handle_redirection_type(shell, input);
    if (result != -1)
        return result;
    return handle_command(shell, input);
}

int has_redirection(const char *cmd)
{
    return has_redirection_out(cmd);
}
