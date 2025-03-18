/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** minishell
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef INCLUDED_MINISHELL_H
    #define INCLUDED_MINISHELL_H

typedef struct shell_s {
    char **env_array;
    int env_size;
    int exit_status;

    char *path;
    char *cmd_name;
    char **cmd_args;
    const char *default_path;
} shell_t;

typedef struct command_context_s {
    shell_t *shell;
    char **commands;
    pid_t *pids;
    int (*pipes)[2];
    int cmd_count;
    int pipe_count;
} command_context_t;

shell_t *init_shell(char **env);
void free_word_array(char **array);
void free_shell(shell_t *shell);
char *get_env_value(shell_t *shell, const char *var);
void set_env_value(shell_t *shell, const char *var, const char *value);
void unset_env_value(shell_t *shell, const char *var);
char *find_executable(shell_t *shell, char *cmd);
int builtin_setenv(shell_t *shell, char **args);
int builtin_unsetenv(shell_t *shell, char **args);
int builtin_cd(shell_t *shell, char **args);
void builtin_echo(shell_t *shell, char **args);
int is_valid_env_name(const char *name);
int handle_builtins(shell_t *shell, char **args);
int unmatched_quotes(const char *input);
int handle_command(shell_t *shell, char *input);
#endif
