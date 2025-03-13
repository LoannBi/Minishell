/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** my_strdup
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(const char *src)
{
    char *dest;
    int i = 0;
    int len;

    if (!src)
        return NULL;
    len = my_strlen(src);
    dest = malloc(sizeof(char) * (len + 1));
    if (!dest)
        return NULL;
    while (i < len) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
