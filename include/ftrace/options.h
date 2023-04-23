/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** options.h
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
#include <stdbool.h>

typedef struct ftrace_options_s {
    bool detailed;
    bool help;
    const char * const *command;
    int pid;
} ftrace_options_t;

int parse_args(ftrace_options_t *options, int argc, char **argv);
