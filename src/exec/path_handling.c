/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** path_handling
*/

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my.h"
#include "exec.h"
#include <sys/stat.h>

static char **split_path(const char *path)
{
    if (!path)
        return NULL;
    return my_str_to_word_array(path, ':');
}

static int is_absolute_path(char *cmd)
{
    return (my_strchr(cmd, '/') != NULL);
}

static char **get_paths(shell_t *shell)
{
    char *path_value = get_env_value(shell, "PATH");

    if (!path_value || !path_value[0]) {
        my_putstr("minishell: PATH is not set\n");
        return split_path((char *)shell->default_path);
    }
    return split_path(path_value);
}

static char *construct_full_path(char *dir, char *cmd)
{
    int len = my_strlen(dir) + my_strlen(cmd) + 2;
    char *full_path = malloc(len);

    if (!full_path)
        return NULL;
    my_strcpy(full_path, dir);
    my_strcat(full_path, "/");
    my_strcat(full_path, cmd);
    return full_path;
}

static char *find_in_paths(char **paths, char *cmd)
{
    struct stat st;
    char *full_path;
    int i = 0;

    if (!paths)
        return NULL;
    while (paths[i]) {
        full_path = construct_full_path(paths[i], cmd);
        if (full_path && stat(full_path, &st) == 0) {
            free_word_array(paths);
            return full_path;
        }
        free(full_path);
        i++;
    }
    return NULL;
}

char *find_executable(shell_t *shell, char *cmd)
{
    char **paths;
    char *found_path;

    if (!cmd || !cmd[0])
        return NULL;
    if (is_absolute_path(cmd))
        return my_strdup(cmd);
    paths = get_paths(shell);
    if (!paths) {
        my_putstr("minishell: memory allocation error\n");
        return NULL;
    }
    found_path = find_in_paths(paths, cmd);
    if (found_path)
        return found_path;
    free_word_array(paths);
    paths = split_path((char *)shell->default_path);
    if (!paths)
        return NULL;
    return find_in_paths(paths, cmd);
}
