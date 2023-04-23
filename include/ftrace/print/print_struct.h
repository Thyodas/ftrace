/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** print_struct.h
*/

#pragma once

#include "print_flag.h"
#include "ftrace/ptrace.h"

static inline int print_value(ftrace_t *data, type_t type, unsigned long value);

static inline int print_struct_stat_p(ftrace_t *data, unsigned long value)
{
    struct stat *st = ptrace_map_data(data->options.pid,
        value, sizeof(struct stat), sizeof(struct stat));
    int written = 0;
    written += fprintf(stderr, "{");
    written += fprintf(stderr, "st_mode=");
    written += print_flag_st_mode(st->st_mode);
    written += fprintf(stderr, ", st_size=");
    written += print_value(data, UNSIGNED, st->st_size);
    written += fprintf(stderr, ", ...}");
    free(st);
    return written;
}

static inline int print_string_table(pid_t pid, unsigned long value)
{
    int written = 0;
    char **table = ptrace_map_data(pid, value, 0, sizeof(char *));
    written += fprintf(stderr, "[");
    for (int i = 0; table[i]; ++i) {
        written += print_string(pid, (unsigned long)table[i]);
        if (table[i + 1] != NULL)
            written += fprintf(stderr, ", ");
    }
    written += fprintf(stderr, "]");
    free(table);
    return written;
}

static inline int print_env_table(ftrace_t *data,
    pid_t pid, unsigned long value)
{
    int written = 0;
    size_t len = 0;
    char **table = ptrace_map_data(pid, value, 0, sizeof(char *));
    for (; table[len]; ++len);
    written += print_value(data, VOID_P, value);
    written += fprintf(stderr, " /* %ld vars */", len);
    free(table);
    return written;
}
