/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** array_utils
*/

#include <stdlib.h>

void free_word_array(char **array)
{
    int i = 0;

    if (!array)
        return;
    while (array[i]) {
        free(array[i]);
        i++;
    }
    free(array);
}
