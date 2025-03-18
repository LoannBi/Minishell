/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** pip_wait
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int handle_signal_status(int status)
{
    int signal_code = WTERMSIG(status);

    if (signal_code == SIGSEGV) {
        my_putstr("Segmentation fault\n");
    } else {
        my_putstr("Killed by signal ");
        my_put_nbr(signal_code);
        my_putchar('\n');
    }
    return 128 + signal_code;
}

static int process_command_status(pid_t pid)
{
    int status = 0;

    if (pid <= 0)
        return 0;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
        return handle_signal_status(status);
    return WEXITSTATUS(status);
}

static int wait_for_commands(pid_t *pids, int cmd_count)
{
    int last_status = 0;

    for (int i = cmd_count - 1; i >= 0; i--)
        last_status = process_command_status(pids[i]);
    return last_status;
}

int execute_pipeline(command_context_t *ctx)
{
    if (launch_commands(ctx) == 84) {
        free_word_array(ctx->commands);
        return 84;
    }
    return wait_for_commands(ctx->pids, ctx->cmd_count);
}
