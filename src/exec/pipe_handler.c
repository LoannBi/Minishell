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

static void cleanup_context(command_context_t *ctx)
{
    if (ctx->commands)
        free_word_array(ctx->commands);
    if (ctx->pids)
        free(ctx->pids);
    if (ctx->pipes)
        free(ctx->pipes);
}

int handle_pipes(shell_t *shell, char *input)
{
    command_context_t ctx;
    int last_status;

    init_command_context(&ctx, shell, input);
    if (prepare_execution(&ctx) == 84) {
        cleanup_context(&ctx);
        return shell->exit_status;
    }
    last_status = execute_pipeline(&ctx);
    cleanup_context(&ctx);
    return last_status;
}
