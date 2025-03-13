/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** my_realloc
*/

#include <stdlib.h>


#include <stdlib.h>

static void copy_memory(char *dest, char *src,
    size_t old_size, size_t new_size)
{
    size_t i = 0;

    while (i < old_size && i < new_size) {
        dest[i] = src[i];
        i++;
    }
}

void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;
    char *src;
    char *dest;

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;
    if (!ptr)
        return new_ptr;
    src = (char *)ptr;
    dest = (char *)new_ptr;
    copy_memory(dest, src, old_size, new_size);
    free(ptr);
    return new_ptr;
}
