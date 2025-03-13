/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** my_atoi
*/

int my_atoi(const char *str)
{
    int result = 0;
    int i = 0;

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}
