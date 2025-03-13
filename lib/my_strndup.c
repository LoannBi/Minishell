/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** my_strndup
*/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "my.h"


char *my_strndup(const char *src, size_t n)
{
    char *dest;
    size_t i = 0;

    if (!src)
        return NULL;
    dest = malloc(sizeof(char) * (n + 1));
    if (!dest)
        return NULL;
    while (i < n && src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
