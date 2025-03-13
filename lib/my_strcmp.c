/*
** EPITECH PROJECT, 2024
** Task06
** File description:
** function like strcmp
*/

int my_strcmp(char const *s1, char const *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    if (*s1 > *s2) {
        return 1;
    } else if (*s1 < *s2) {
        return -1;
    } else {
        return 0;
    }
}
