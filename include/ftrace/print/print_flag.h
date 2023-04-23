/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** print_flag.h
*/

#pragma once

#include "ftrace/data.h"

static inline char *get_flag_st_mode_ftype(mode_t value)
{
    switch (value & S_IFMT) {
        case S_IFREG:
            return "S_IFREG";
        case S_IFDIR:
            return "S_IFDIR";
        case S_IFCHR:
            return "S_IFCHR";
        case S_IFBLK:
            return "S_IFBLK";
        default:
            return NULL;
    }
}

static inline int print_flag_st_mode(mode_t value)
{
    int written = 0;
    char *ftype = get_flag_st_mode_ftype(value);
    if (ftype == NULL)
        written += fprintf(stderr, "%#o", value & S_IFMT);
    else
        written += fprintf(stderr, "%s", ftype);
    written += fprintf(stderr, "|");
    written += fprintf(stderr, "%#o", value & ~S_IFMT);
    return written;
}
