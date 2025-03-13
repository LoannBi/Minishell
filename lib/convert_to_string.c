/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** convert_to_string
*/

#include <stddef.h>

static void append_prefix(char *dest, const char *prefix, int *index)
{
    while (*prefix) {
        dest[*index] = *prefix;
        (*index)++;
        prefix++;
    }
}

static void handle_negative_value(char *dest, int *value, int *index)
{
    if (*value < 0) {
        dest[*index] = '-';
        (*index)++;
        *value = - *value;
    }
}

static void convert_value_to_string(char *dest, int value, int *index)
{
    char temp[12];
    int temp_index = 0;
    int digit = 0;

    if (value == 0) {
        dest[*index] = '0';
        (*index)++;
        return;
    }
    while (value > 0) {
        digit = value % 10;
        temp[temp_index] = digit + '0';
        temp_index++;
        value /= 10;
    }
    while (temp_index > 0) {
        temp_index--;
        dest[*index] = temp[temp_index];
        (*index)++;
    }
}

void convert_to_string(char *dest, const char *prefix, int value)
{
    int index = 0;

    append_prefix(dest, prefix, &index);
    handle_negative_value(dest, &value, &index);
    convert_value_to_string(dest, value, &index);
    dest[index] = '\0';
}
