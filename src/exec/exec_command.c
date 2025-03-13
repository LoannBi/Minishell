/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** exec_command
*/
#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include "my.h"


static void print_signal_message(int sig)
{
    if (sig == SIGSEGV)
        my_putstr("Segmentation fault (core dumped)\n");
    else if (sig == SIGFPE)
        my_putstr("Floating exception (core dumped)\n");
}

void check_process_status(int status)
{
    if (WIFSIGNALED(status)) {
        print_signal_message(WTERMSIG(status));
    }
}

static void handle_exec_error(char *cmd_path)
{
    if (errno == ENOEXEC) {
        my_putstr(cmd_path);
        my_putstr(": Exec format error. Binary file not executable.\n");
    } else {
        my_putstr(cmd_path);
        my_putstr(": ");
        my_putstr(strerror(errno));
        my_putchar('\n');
    }
    exit(1);
}

static int check_executable(char *cmd_path)
{
    struct stat sb;

    if (stat(cmd_path, &sb) == -1) {
        my_putstr(cmd_path);
        my_putstr(": ");
        my_putstr(strerror(errno));
        my_putchar('\n');
        return 1;
    }
    if (!S_ISREG(sb.st_mode) || access(cmd_path, X_OK) == -1) {
        my_putstr(cmd_path);
        my_putstr(": Permission denied.\n");
        return 1;
    }
    return 0;
}

static void execute_child_process(char *cmd_path, char **args, char **env)
{
    if (check_executable(cmd_path))
        exit(1);
    execve(cmd_path, args, env);
    handle_exec_error(cmd_path);
}

int execute_command(shell_t *shell, char *cmd_path, char **args)
{
    pid_t pid = fork();
    int status;

    if (pid == -1) {
        perror("fork");
        return 84;
    }
    if (pid == 0)
        execute_child_process(cmd_path, args, shell->env_array);
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
        shell->exit_status = 128 + WTERMSIG(status);
        check_process_status(status);
    } else if (WIFEXITED(status)) {
        shell->exit_status = WEXITSTATUS(status);
    }
    return shell->exit_status;
}
