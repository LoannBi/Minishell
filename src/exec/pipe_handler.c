/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** pipe_handler
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int handle_pipes(shell_t *shell, char *input)
{
    command_context_t ctx;
    int last_status;

    init_command_context(&ctx, shell, input);
    if (prepare_execution(&ctx) == 84)
        return 84;
    last_status = execute_pipeline(&ctx);
    free(ctx.pids);
    free(ctx.pipes);
    free_word_array(ctx.commands);
    return last_status;
}
