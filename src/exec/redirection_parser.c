/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** redirection_parser
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
#include <errno.h>

static redirection_type_t get_redirection_type(const char *cmd, int index)
{
    if (cmd[index] == '>' && cmd[index + 1] == '>')
        return REDIR_APPEND;
    return REDIR_OUT;
}

static int find_redirection_index(const char *cmd, redirection_type_t *type)
{
    int i;
    int in_quotes;

    i = 0;
    in_quotes = 0;
    while (cmd[i]) {
        if (cmd[i] == '"' || cmd[i] == '\'')
            in_quotes = !in_quotes;
        if (!in_quotes && cmd[i] == '>') {
            *type = get_redirection_type(cmd, i);
            return i;
        }
        i++;
    }
    return -1;
}

static char *extract_redirection_file(const char *cmd)
{
    char *trimmed;

    if (!cmd || !cmd[0]) {
        print_error("Missing name for redirect.\n");
        return NULL;
    }
    trimmed = clean_str(cmd);
    if (!trimmed)
        return NULL;
    if (!trimmed[0]) {
        free(trimmed);
        print_error("Missing name for redirect.\n");
        return NULL;
    }
    return trimmed;
}

static int is_redirection_symbol(const char *cmd, int i)
{
    if (cmd[i] == '>' && cmd[i + 1] == '>')
        return 2;
    if (cmd[i] == '>')
        return 1;
    return 0;
}

static int should_toggle_quotes(char c)
{
    return (c == '"' || c == '\'');
}

static int update_and_check_skip(const char *cmd, int *i, int *count)
{
    int skip;

    skip = is_redirection_symbol(cmd, *i);
    if (skip > 0) {
        (*count)++;
        *i += skip;
        return 1;
    }
    return 0;
}

int has_redirection_out(const char *cmd)
{
    int i;
    int in_quotes;

    i = 0;
    in_quotes = 0;
    while (cmd[i]){
        if (cmd[i] == '"' || cmd[i] == '\'')
            in_quotes = !in_quotes;
        if (!in_quotes && cmd[i] == '>')
            return 1;
        i++;
    }
    return 0;
}

int has_multiple_redirections(const char *cmd)
{
    int i;
    int in_quotes;
    int count;

    i = 0;
    in_quotes = 0;
    count = 0;
    while (cmd[i]) {
        if (should_toggle_quotes(cmd[i]))
            in_quotes = !in_quotes;
        if (!in_quotes && update_and_check_skip(cmd, &i, &count))
            continue;
        i++;
    }
    return (count > 1);
}

int check_redirection_syntax(char *command_part, char *file_part)
{
    if (!command_part || !file_part) {
        if (command_part)
            free(command_part);
        return 1;
    }
    return 0;
}

char *extract_command_part(const char *cmd, char **file_ptr,
    redirection_type_t *type)
{
    int index;
    int offset;
    char *command_part;
    char *file_part;

    *type = REDIR_NONE;
    index = find_redirection_index(cmd, type);
    if (index < 0)
        return NULL;
    command_part = my_strndup(cmd, index);
    if (!command_part)
        return NULL;
    offset = (*type == REDIR_APPEND) ? 2 : 1;
    file_part = extract_redirection_file(&cmd[index + offset]);
    if (!file_part) {
        free(command_part);
        return NULL;
    }
    *file_ptr = file_part;
    return command_part;
}
