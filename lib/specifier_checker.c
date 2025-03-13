/*
** EPITECH PROJECT, 2024
** B-CPE-101-NAN-1-1-miniprintf-loann.bideau
** File description:
** specifier_checker
*/
#include "my.h"
#include <stdarg.h>

int specifier_int(va_list args)
{
    int nb = va_arg(args, int);

    return my_put_nbr(nb);
}

int specifier_str(va_list args)
{
    char *str = va_arg(args, char *);

    return my_putstr(str);
}

int specifier_char(va_list args)
{
    char ch = (char) va_arg(args, int);

    my_putchar(ch);
    return 1;
}

int specifier_pourcent(void)
{
    my_putchar('%');
    return 1;
}

int specifier_checker(char specifier, va_list args)
{
    if (specifier == 'd' || specifier == 'i') {
        return specifier_int(args);
    }
    if (specifier == 's') {
        return specifier_str(args);
    }
    if (specifier == 'c') {
        return specifier_char(args);
    }
    if (specifier == '%') {
        return specifier_pourcent();
    }
    return 0;
}
