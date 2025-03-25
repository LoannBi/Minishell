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

static int is_unreadable_or_missing(const char *file)
{
    if (access(file, F_OK) == -1) {
        print_error(file);
        print_error(": No such file or directory.\n");
        return 1;
    }
    if (access(file, R_OK) == -1) {
        print_error(file);
        print_error(": Permission denied.\n");
        return 1;
    }
    return 0;
}

static int is_directory_path(const char *file)
{
    struct stat st;

    if (stat(file, &st) == 0 && S_ISDIR(st.st_mode)) {
        print_error(file);
        print_error(": Is a directory.\n");
        return 1;
    }
    return 0;
}

static int open_input_file(const char *file)
{
    int fd;

    if (is_unreadable_or_missing(file))
        return -1;
    if (is_directory_path(file))
        return -1;
    fd = open(file, O_RDONLY);
    if (fd == -1) {
        print_error(file);
        print_error(": ");
        print_error_message_by_errno();
        return -1;
    }
    return fd;
}

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

static int handle_open_error(const char *file)
{
    print_error(file);
    print_error(": ");
    print_error_message_by_errno();
    return -1;
}

static int handle_input_redirection(const char *file)
{
    int fd;
    int old_fd;

    old_fd = dup(STDIN_FILENO);
    if (old_fd == -1)
        return -1;
    fd = open_input_file(file);
    if (fd == -1) {
        close(old_fd);
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        print_error("Error redirecting input.\n");
        close(fd);
        close(old_fd);
        return -1;
    }
    close(fd);
    return old_fd;
}

static int handle_output_redirection(const char *file, redirection_type_t type)
{
    int fd;
    int old_fd;

    old_fd = dup(STDOUT_FILENO);
    if (old_fd == -1)
        return -1;
    fd = open_redirection_file(file, type);
    if (fd == -1) {
        close(old_fd);
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        print_error("Error redirecting output.\n");
        close(fd);
        close(old_fd);
        return -1;
    }
    close(fd);
    return old_fd;
}

int apply_redirection(const char *file, redirection_type_t type)
{
    if (type == REDIR_IN)
        return handle_input_redirection(file);
    return handle_output_redirection(file, type);
}

int apply_redirection_out(const char *file, redirection_type_t type)
{
    return apply_redirection(file, type);
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
