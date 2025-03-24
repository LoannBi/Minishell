/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** redirection_utils
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

int has_redirection_out(const char *cmd)
{
    int i;
    int in_quotes;

    i = 0;
    in_quotes = 0;
    while (cmd[i]) {
        if (cmd[i] == '"' || cmd[i] == '\'')
            in_quotes = !in_quotes;
        if (!in_quotes && cmd[i] == '>')
            return 1;
        i++;
    }
    return 0;
}

static int find_redirection_index(const char *cmd)
{
    int i;
    int in_quotes;

    i = 0;
    in_quotes = 0;
    while (cmd[i]) {
        if (cmd[i] == '"' || cmd[i] == '\'')
            in_quotes = !in_quotes;
        if (!in_quotes && cmd[i] == '>')
            return i;
        i++;
    }
    return -1;
}

static char *extract_redirection_file(const char *cmd)
{
    char *trimmed;

    trimmed = clean_str(cmd);
    if (!trimmed)
        return NULL;
    if (!trimmed[0]) {
        free(trimmed);
        return NULL;
    }
    return trimmed;
}

char *extract_command_part(const char *cmd, char **file_ptr)
{
    int index;
    char *command_part;
    char *file_part;

    index = find_redirection_index(cmd);
    if (index < 0)
        return NULL;
    command_part = my_strndup(cmd, index);
    if (!command_part)
        return NULL;
    file_part = extract_redirection_file(&cmd[index + 1]);
    if (!file_part) {
        free(command_part);
        return NULL;
    }
    *file_ptr = file_part;
    return command_part;
}

int open_redirection_file(const char *file)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        print_error(file);
        print_error(": Cannot create file.\n");
        return -1;
    }
    return fd;
}

int apply_redirection_out(const char *file)
{
    int fd;
    int old_stdout;

    old_stdout = dup(STDOUT_FILENO);
    if (old_stdout == -1)
        return -1;
    fd = open_redirection_file(file);
    if (fd == -1) {
        close(old_stdout);
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        print_error("Error redirecting output.\n");
        close(fd);
        close(old_stdout);
        return -1;
    }
    close(fd);
    return old_stdout;
}

int check_redirection_syntax(char *command_part, char *file_part)
{
    if (!command_part || !file_part) {
        print_error("Invalid redirection syntax.\n");
        if (command_part)
            free(command_part);
        if (file_part)
            free(file_part);
        return 1;
    }
    return 0;
}
