/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** pip_exec
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void close_all_pipes(int pipe_count, int pipes[][2])
{
    int i;

    for (i = 0; i < pipe_count; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

static void redirect_io(command_context_t *ctx, int index)
{
    if (index > 0 && dup2(ctx->pipes[index - 1][0], STDIN_FILENO) == -1) {
        perror("dup2 stdin");
        exit(1);
    }
    if (index < ctx->cmd_count - 1 &&
        dup2(ctx->pipes[index][1], STDOUT_FILENO) == -1) {
        perror("dup2 stdout");
        exit(1);
    }
}

static void execute_child(command_context_t *ctx, char **args, int index)
{
    char *cmd_path;

    redirect_io(ctx, index);
    close_all_pipes(ctx->pipe_count, ctx->pipes);
    if (handle_builtins(ctx->shell, args))
        exit(ctx->shell->exit_status);
    cmd_path = find_executable(ctx->shell, args[0]);
    if (!cmd_path) {
        my_putstr(args[0]);
        my_putstr(": Command not found.\n");
        exit(1);
    }
    execve(cmd_path, args, ctx->shell->env_array);
    free(cmd_path);
    perror("execve");
    exit(1);
}

static void handle_parent_process(command_context_t *ctx, int index)
{
    if (index > 0)
        close(ctx->pipes[index - 1][0]);
    if (index < ctx->cmd_count - 1)
        close(ctx->pipes[index][1]);
}

static char **get_command_arguments(command_context_t *ctx, int index)
{
    char **args = my_str_to_word_array(ctx->commands[index], ' ');

    if (!args)
        ctx->pids[index] = -1;
    return args;
}

int create_and_execute_process(command_context_t *ctx, char **args, int index)
{
    ctx->pids[index] = fork();
    if (ctx->pids[index] == -1) {
        perror("fork");
        free_word_array(args);
        close_all_pipes(ctx->pipe_count, ctx->pipes);
        return 84;
    }
    if (ctx->pids[index] == 0)
        execute_child(ctx, args, index);
    else
        handle_parent_process(ctx, index);
    free_word_array(args);
    return 0;
}

int launch_commands(command_context_t *ctx)
{
    int i;
    char **args;

    for (i = 0; i < ctx->cmd_count; i++) {
        args = get_command_arguments(ctx, i);
        if (!args)
            continue;
        if (create_and_execute_process(ctx, args, i) == 84)
            return 84;
    }
    return 0;
}
