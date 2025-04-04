/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** error_handling
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

int is_valid_env_name(const char *name)
{
    int i = 0;

    if (!name || !name[0])
        return 0;
    while (name[i]) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
            (name[i] >= 'a' && name[i] <= 'z') ||
            (name[i] >= '0' && name[i] <= '9') ||
            name[i] == '_'))
            return 0;
        i++;
    }
    return 1;
}

int unmatched_quotes(const char *input)
{
    int double_quotes = 0;
    int single_quotes = 0;

    for (int i = 0; input[i]; i++) {
        if (input[i] == '"')
            double_quotes = !double_quotes;
        if (input[i] == '\'')
            single_quotes = !single_quotes;
    }
    if (double_quotes) {
        my_putstr("Unmatched '\"'.\n");
        return 1;
    }
    if (single_quotes) {
        my_putstr("Unmatched '\''.\n");
        return 1;
    }
    return 0;
}

void print_error_message_by_errno(void)
{
    if (errno == ENOENT) {
        print_error("No such file or directory.\n");
        return;
    }
    if (errno == EACCES || errno == EPERM) {
        print_error("Permission denied.\n");
        return;
    }
    if (errno == EISDIR) {
        print_error("Is a directory.\n");
        return;
    }
    print_error("Cannot create file.\n");
}
