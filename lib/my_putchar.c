/*
** EPITECH PROJECT, 2024
** My_ls_project
** File description:
** my_putchar (copy)
*/

#include <unistd.h>

void my_putchar(char c)
{
    ssize_t result = write(1, &c, 1);

    if (result == -1) {
        return;
    }
}
