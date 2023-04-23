/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ftrace.h
*/

#pragma once

#include "options.h"

#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

typedef struct {
    ftrace_options_t options;
    struct user_regs_struct regs;
} ftrace_t;
