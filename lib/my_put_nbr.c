/*
** EPITECH PROJECT, 2024
** task07
** File description:
** task07
*/

#include "my.h"

int my_put_nbr(int n)
{
    int count = 0;

    if (n < 0) {
        my_putchar('-');
        count++;
        n = -n;
    }
    if (n > 9) {
        count += my_put_nbr(n / 10);
    }
    my_putchar('0' + n % 10);
    count++;
    return count;
}
