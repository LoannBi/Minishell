/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** main
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int read_user_input(char **input, size_t *len)
{
    ssize_t read;

    if (isatty(STDIN_FILENO))
        my_putstr("$> ");
    read = getline(input, len, stdin);
    if (read == -1)
        return 84;
    if ((*input)[read - 1] == '\n')
        (*input)[read - 1] = '\0';
    return 0;
}

int main(int argc, char **argv, char **env)
{
    shell_t *shell = init_shell(env);
    char *input = NULL;
    size_t len = 0;
    int final_exit_status;

    (void)argc;
    (void)argv;
    if (!shell)
        return 84;
    while (1) {
        if (read_user_input(&input, &len) == 84)
            break;
        shell->exit_status = handle_line(shell, input);
    }
    final_exit_status = shell->exit_status;
    free(input);
    free_shell(shell);
    return final_exit_status;
}
