/*
** EPITECH PROJECT, 2024
** task02
** File description:
** task02
*/

#include "my.h"

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
    return i;
}
