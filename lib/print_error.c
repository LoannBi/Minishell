/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** print_error
*/

#include <unistd.h>
#include <string.h>

void print_error(const char *message)
{
    write(STDERR_FILENO, message, strlen(message));
}
