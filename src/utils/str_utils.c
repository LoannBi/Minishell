/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** str_utils
*/

#include <stdlib.h>
#include "my.h"

static char *allocate_cleaned_str(const char *str)
{
    char *cleaned = malloc(my_strlen(str) + 1);

    if (!cleaned)
        return NULL;
    return cleaned;
}

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

static void append_character(char *cleaned, char c, int *j)
{
    cleaned[*j] = c;
    (*j)++;
}

static void process_char(char *cleaned, const char **str_ptr,
    int *j, int *in_word)
{
    if (!is_whitespace(**str_ptr)) {
        append_character(cleaned, **str_ptr, j);
        *in_word = 1;
        return;
    }
    if (*in_word) {
        append_character(cleaned, ' ', j);
        *in_word = 0;
    }
}

static void copy_characters(const char *str, char *cleaned, int *j)
{
    int in_word = 0;

    while (*str) {
        process_char(cleaned, &str, j, &in_word);
        str++;
    }
}

static void remove_trailing_space(char *cleaned, int *j)
{
    if (*j > 0 && cleaned[*j - 1] == ' ')
        (*j)--;
}

char *clean_str(const char *str)
{
    char *cleaned;
    int j = 0;

    if (!str)
        return NULL;
    cleaned = allocate_cleaned_str(str);
    if (!cleaned)
        return NULL;
    copy_characters(str, cleaned, &j);
    remove_trailing_space(cleaned, &j);
    cleaned[j] = '\0';
    return cleaned;
}
