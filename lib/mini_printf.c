/*
** EPITECH PROJECT, 2024
** B-CPE-101-NAN-1-1-miniprintf-loann.bideau
** File description:
** miniprintf
*/

#include <stdarg.h>
#include <unistd.h>
#include "my.h"

int mini_printf(const char *format, ...)
{
    int letter_count = 0;
    va_list args;

    va_start(args, format);
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            letter_count += specifier_checker(*format, args);
        } else {
            my_putchar(*format);
            letter_count++;
        }
        format++;
    }
    va_end(args);
    return letter_count;
}
