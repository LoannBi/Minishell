/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** line_handlers
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int process_command_block(shell_t *shell, char *block)
{
    char *cleaned;
    int status = 0;

    cleaned = clean_str(block);
    if (!cleaned)
        return status;
    if (cleaned[0] == '\0') {
        free(cleaned);
        return status;
    }
    status = handle_command(shell, cleaned);
    free(cleaned);
    return status;
}

int handle_line(shell_t *shell, char *input)
{
    char **blocks;
    int last_status = 0;
    int i;

    blocks = my_str_to_word_array(input, ';');
    if (!blocks)
        return 84;
    for (i = 0; blocks[i] != NULL; i++)
        last_status = process_command_block(shell, blocks[i]);
    free_word_array(blocks);
    return last_status;
}
