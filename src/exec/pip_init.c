/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** pip_init
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int count_pipes(char *input)
{
    int count = 0;
    int i = 0;

    if (!input)
        return 0;
    while (input[i]) {
        if (input[i] == '|')
            count++;
        i++;
    }
    return count;
}

static char **split_by_pipe(char *input)
{
    return my_str_to_word_array(input, '|');
}

static void clean_commands(char **commands, int cmd_count)
{
    int i;
    char *cleaned;

    for (i = 0; i < cmd_count; i++) {
        if (!commands[i])
            continue;
        cleaned = clean_str(commands[i]);
        if (cleaned) {
            free(commands[i]);
            commands[i] = cleaned;
        }
    }
}

void init_command_context(command_context_t *ctx, shell_t *shell, char *input)
{
    ctx->shell = shell;
    ctx->cmd_count = count_pipes(input) + 1;
    ctx->pipe_count = ctx->cmd_count - 1;
    ctx->commands = split_by_pipe(input);
    if (!ctx->commands) {
        ctx->pids = NULL;
        ctx->pipes = NULL;
        return;
    }
    ctx->pids = malloc(sizeof(pid_t) * ctx->cmd_count);
    ctx->pipes = malloc(sizeof(int[2]) * ctx->pipe_count);
}

int create_pipes(int pipe_count, int pipes[][2])
{
    int i;
    int result;

    for (i = 0; i < pipe_count; i++) {
        result = pipe(pipes[i]);
        if (result == -1) {
            perror("pipe");
            return 84;
        }
    }
    return 0;
}

int prepare_execution(command_context_t *ctx)
{
    if (!ctx->commands || !ctx->pids || !ctx->pipes)
        return 84;
    clean_commands(ctx->commands, ctx->cmd_count);
    if (create_pipes(ctx->pipe_count, ctx->pipes) == 84) {
        free_word_array(ctx->commands);
        return 84;
    }
    return 0;
}
