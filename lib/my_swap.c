/*
** EPITECH PROJECT, 2024
** my_swap
** File description:
** wapt the content of two integers
*/

#include <string.h>

void my_swap(char **a, char **b)
{
    char *temp = *a;

    *a = *b;
    *b = temp;
}
