/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ftrace.h
*/

#pragma once

#include "options.h"
#include "vector.h"

#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

/*
    #define INS_BYTES_TO_INT32(bytes, offset) (                 \
    (int64_t)(bytes[offset] | (bytes[offset + 1] << 8)          \
    | (bytes[offset + 2] << 16) | (bytes[offset + 3] << 24))    \
)
*/

typedef union {
    int64_t longs[2];
    u_int8_t bytes[16];
} instruction_t;

typedef char * string_t;
typedef vector_struct(string_t) string_vector_t;

typedef struct {
    ftrace_options_t options;
    struct user_regs_struct regs;
    instruction_t instruction;
    FILE *proc_maps;
    string_vector_t func_names;
    int nb_call;
    int nb_ret;
} ftrace_t;

#define STR2(x) #x
#define STR(X) STR2(X)
