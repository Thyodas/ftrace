/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** print.h
*/

#pragma once

#include "ftrace/data.h"
#include "ftrace/syscall.h"

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "print_simple.h"
#include "print_struct.h"
#include "print_flag.h"

static inline int print_value_simple(type_t type, unsigned long value)
{
    switch (type) {
        case VOID:
            return print_void();
        default:
            return fprintf(stderr, "%#lx", value);
    }
}

static inline int print_value_detailed(ftrace_t *data, type_t type,
    unsigned long value)
{
    switch (type) {
        case NUM:
            return print_num(value);
        case UNSIGNED:
            return print_unsigned(value);
        case VOID:
            return print_void();
        case STRING:
            return print_string(data->options.pid, value);
        case STRUCT_STAT_P:
            return print_struct_stat_p(data, value);
        case STRING_TABLE:
            return print_string_table(data->options.pid, value);
        case ENV_TABLE:
            return print_env_table(data, data->options.pid, value);
        default:
            return print_address(value);
    }
}

static inline int print_value(ftrace_t *data, type_t type, unsigned long value)
{
    if (data->options.detailed)
        return print_value_detailed(data, type, value);
    else
        return print_value_simple(type, value);
}
