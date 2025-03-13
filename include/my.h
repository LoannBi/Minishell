/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** my
*/

#include <stdarg.h>
#include <stddef.h>

#ifndef INCLUDED_MY_H
    #define INCLUDED_MY_H

char *my_strdup(const char *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strchr(const char *str, int c);
void convert_to_string(char *dest, const char *prefix, int value);
int mini_printf(const char *format, ...);
int my_atoi(const char *str);
int my_put_nbr(int n);
void my_putchar(char c);
int my_putstr(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
int my_strlen(char const *str);
void my_swap(char **a, char **b);
int specifier_checker(char specifier, va_list args);
void *my_realloc(void *ptr, size_t old_size, size_t new_size);
int my_strncmp(char const *s1, char const *s2, int n);
char **my_str_to_word_array(const char *str, char delim);
char *my_strndup(const char *src, size_t n);
char *clean_str(const char *str);
#endif
