/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** my_strncmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (!s1 || !s2 || n <= 0)
        return 0;
    while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
        i++;
    if (i == n)
        return 0;
    return s1[i] - s2[i];
}
