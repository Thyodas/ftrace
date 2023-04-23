/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** print_simple.h
*/

#pragma once

#include "ftrace/ptrace.h"
#include "ftrace/data.h"
#include "ftrace/syscall.h"

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static inline int print_address(unsigned long value)
{
    if (value == 0)
        return fprintf(stderr, "NULL");
    return fprintf(stderr, "%#lx", value);
}

static inline int print_num(unsigned long value)
{
    return fprintf(stderr, "%ld", *(long *)&value);
}

static inline int print_unsigned(unsigned long value)
{
    return fprintf(stderr, "%lu", value);
}

static inline int print_void(void)
{
    return fprintf(stderr, "?");
}

static inline int print_string(pid_t pid, unsigned long value)
{
    char *str = ptrace_map_data(pid, value, 0, 1);
    size_t i = 0;
    int written = 0;
    bool overflow = false;
    written += fprintf(stderr, "\"");
    for (; str[i] != '\0'; ++i) {
        if (i > 32) {
            overflow = true;
            break;
        }
        if (isprint(str[i]))
            written += fprintf(stderr, "%c", str[i]);
        else
            written += fprintf(stderr, "\\%d", str[i]);
    }
    written += fprintf(stderr, "\"");
    if (overflow)
        written += fprintf(stderr, "...");
    free(str);
    return written;
}
