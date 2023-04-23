/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** print.c
*/

#include <stdio.h>
#include <string.h>
#include <sys/user.h>

#include "ftrace/error.h"
#include "ftrace/syscall.h"
#include "ftrace/data.h"
#include "ftrace/print/print.h"

int ptrace_getregs(int pid, struct user_regs_struct *regs);

static void print_syscall_output(ftrace_t *data, type_t type,
    unsigned long output)
{
    if (output > -4096UL) {
        unsigned long syscall_errno = -output;
        if (syscall_errno >= ERRNO_NB)
            syscall_errno = 0;
        fprintf(stderr, "-1 %s (%s)\n", errno_names[syscall_errno],
            strerror(syscall_errno));
    } else {
        print_value(data, type, output);
        fprintf(stderr, "\n");
    }
}

int print_syscall(ftrace_t *data, struct user_regs_struct *regs)
{
    int written = 0;
    unsigned long args[6] = {regs->rdi, regs->rsi, regs->rdx, regs->r10,
        regs->r8, regs->r9};
    syscall_t *syscall = &syscall_table[regs->orig_rax];
    type_t types[6] = {syscall->arg_type0, syscall->arg_type1,
        syscall->arg_type2, syscall->arg_type3, syscall->arg_type4,
        syscall->arg_type5};
    written += fprintf(stderr, "Syscall %s(", syscall->syscall_name);
    for (int i = 0 ; i < syscall->type_nb ; ++i) {
        written += print_value(data, types[i], args[i]);
        if (i + 1 < syscall->type_nb)
            written += fprintf(stderr, ", ");
    }
    fprintf(stderr, ") %*s", written >= 40 ? 0 : 40 - written,
        "= ");
    print_syscall_output(data, syscall->return_type, regs->rax);
    return 0;
}
