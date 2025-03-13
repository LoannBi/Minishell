/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** builtin_cd
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "my.h"
#include <sys/stat.h>

static void update_oldpwd(shell_t *shell, char *old_pwd)
{
    if (!old_pwd)
        return;
    set_env_value(shell, "OLDPWD", old_pwd);
}

static char *get_target_directory(shell_t *shell, char *arg)
{
    char *oldpwd_value;

    if (!arg || my_strcmp(arg, "") == 0)
        return get_env_value(shell, "HOME");
    if (my_strcmp(arg, "..") == 0)
        return "..";
    if (my_strcmp(arg, "-") == 0) {
        oldpwd_value = get_env_value(shell, "OLDPWD");
        if (!oldpwd_value) {
            my_putstr(": No such file or directory.\n");
            shell->exit_status = 1;
            return NULL;
        }
        return oldpwd_value;
    }
    return arg;
}

static int check_cd_conditions(shell_t *shell, char *target_dir, char *old_pwd)
{
    struct stat path_stat;

    if (!target_dir) {
        my_putstr("cd: HOME not set\n");
        shell->exit_status = 1;
        free(old_pwd);
        return 1;
    }
    if (stat(target_dir, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode)) {
        my_putstr(target_dir);
        my_putstr(": Not a directory.\n");
        shell->exit_status = 1;
        free(old_pwd);
        return 1;
    }
    return 0;
}

static int handle_cd_errors(shell_t *shell, char *target_dir, char *old_pwd)
{
    if (check_cd_conditions(shell, target_dir, old_pwd))
        return 1;
    if (chdir(target_dir) == -1) {
        my_putstr(target_dir);
        my_putstr(": No such file or directory.\n");
        shell->exit_status = 1;
        free(old_pwd);
        return 1;
    }
    return 0;
}

int builtin_cd(shell_t *shell, char **args)
{
    char *old_pwd = getcwd(NULL, 0);
    char *target_dir = get_target_directory(shell, args[1]);

    if (!target_dir) {
        if (args[1] && my_strcmp(args[1], "-") == 0)
            return 1;
        my_putstr("cd: HOME not set\n");
        shell->exit_status = 1;
        free(old_pwd);
        return 1;
    }
    if (handle_cd_errors(shell, target_dir, old_pwd))
        return 1;
    update_oldpwd(shell, old_pwd);
    free(old_pwd);
    return 0;
}
