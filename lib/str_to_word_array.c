/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** step3
*/

#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "minishell.h"
#include "exec.h"

static int count_words(const char *str, char delim)
{
    int count = 1;
    int i = 0;

    while (str[i]) {
        if (str[i] == delim)
            count++;
        i++;
    }
    return count;
}

static char **allocate_word_array(const char *str, char delim)
{
    int count = count_words(str, delim);
    char **array = malloc(sizeof(char *) * (count + 1));

    if (!array)
        return NULL;
    return array;
}

static void free_array_on_failure(char **array, int i)
{
    while (i > 0) {
        free(array[i - 1]);
        i--;
    }
    free(array);
}

static int add_word_to_array(char **array, const char *str, int *indexes)
{
    int len = indexes[1] - indexes[0] + (str[indexes[1] + 1] == '\0');

    array[indexes[2]] = my_strndup(str + indexes[0], len);
    if (!array[indexes[2]]) {
        free_array_on_failure(array, indexes[2]);
        return 84;
    }
    return 0;
}

static int process_string_to_array(char **array, const char *str, char delim)
{
    int indexes[3] = {0, 0, 0};

    while (str[indexes[1]]) {
        if (str[indexes[1]] != delim && str[indexes[1] + 1] != '\0') {
            indexes[1]++;
            continue;
        }
        if (add_word_to_array(array, str, indexes) == 84)
            return 84;
        indexes[2]++;
        indexes[0] = indexes[1] + 1;
        indexes[1]++;
    }
    array[indexes[2]] = NULL;
    return 0;
}

char **my_str_to_word_array(const char *str, char delim)
{
    char **array;

    if (!str)
        return NULL;
    array = allocate_word_array(str, delim);
    if (!array)
        return NULL;
    if (process_string_to_array(array, str, delim) == 84)
        return NULL;
    return array;
}
