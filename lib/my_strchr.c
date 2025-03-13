/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** my_strchr
*/

#include <stddef.h>

char *my_strchr(const char *str, int c)
{
    int i = 0;

    if (!str)
        return NULL;
    while (str[i] != '\0') {
        if (str[i] == (char)c)
            return (char *)&str[i];
        i++;
    }
    if (c == '\0')
        return (char *)&str[i];
    return NULL;
}
