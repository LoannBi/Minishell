/*
** EPITECH PROJECT, 2024
** task03
** File description:
** my_strlen
*/

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i += 1;
    }
    return i;
}
