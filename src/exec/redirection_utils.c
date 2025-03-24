/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** redirection_utils
*/

#include "minishell.h"
#include "my.h"
#include "exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

static int is_directory(const char *file)
{
    struct stat st;

    if (stat(file, &st) == 0 && S_ISDIR(st.st_mode)) {
        print_error(file);
        print_error(": Is a directory.\n");
        return 1;
    }
    return 0;
}

static void print_error_message_by_errno(void)
{
    if (errno == ENOENT) {
        print_error("No such file or directory.\n");
        return;
    }
    if (errno == EACCES || errno == EPERM) {
        print_error("Permission denied.\n");
        return;
    }
    if (errno == EISDIR) {
        print_error("Is a directory.\n");
        return;
    }
    print_error("Cannot create file.\n");
}

static int handle_open_error(const char *file)
{
    print_error(file);
    print_error(": ");
    print_error_message_by_errno();
    return -1;
}

int open_redirection_file(const char *file, redirection_type_t type)
{
    int fd;
    int flags;

    if (is_directory(file))
        return -1;
    flags = O_WRONLY | O_CREAT;
    if (type == REDIR_APPEND)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    fd = open(file, flags, 0777);
    if (fd == -1)
        return handle_open_error(file);
    return fd;
}

int apply_redirection_out(const char *file, redirection_type_t type)
{
    int fd;
    int old_stdout;

    old_stdout = dup(STDOUT_FILENO);
    if (old_stdout == -1)
        return -1;
    fd = open_redirection_file(file, type);
    if (fd == -1) {
        close(old_stdout);
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        print_error("Error redirecting output.\n");
        close(fd);
        close(old_stdout);
        return -1;
    }
    close(fd);
    return old_stdout;
}
