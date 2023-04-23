/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ftrace.c
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "ftrace/data.h"
#include "ftrace/syscall.h"
#include "ftrace/ptrace.h"

char *get_executable(const char *executable_name);
int print_syscall(ftrace_t *data, struct user_regs_struct *regs);
void print_signals(int signum);

static int execute_program(ftrace_t *data)
{
    char *executable = get_executable(data->options.command[0]);
    if (executable == NULL) {
        fprintf(stderr, "ftrace: Can't stat '%s': %s\n",
            data->options.command[0], strerror(errno));
        return 84;
    }
    int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "ftrace: Can't fork: %s\n", strerror(errno));
        return 84;
    }
    if (pid != 0) {
        data->options.pid = pid;
        free(executable);
        return 0;
    }
    execv(executable, (char *const *)data->options.command);
    return 0;
}

/*
if ((opcode & 0xff) == 0xe8)
    fprintf(stderr, "Entering function opcode: %lx\n", opcode);
*/

int trace_signals(int status)
{
    if (WIFSIGNALED(status)) {
        print_signals(WTERMSIG(status));
        return 1;
    }
    if (WSTOPSIG(status) != SIGTRAP) {
        print_signals(WSTOPSIG(status));
        return 1;
    }
    return 0;
}

int trace_execution(ftrace_t *data, int status)
{
    long opcode = ptrace(PTRACE_PEEKTEXT, data->options.pid, data->regs.rip, 0);

    if (ptrace_getregs(data->options.pid, &data->regs)
        || (opcode == -1 && errno != 0) || data->regs.orig_rax > SYSCALL_NB) {
        return 1;
    }
    if (WSTOPSIG(status) == SIGTRAP && (opcode & 0xffff) == 0x050f)
        print_syscall(data, &data->regs);
    return 0;
}

int start_ftrace(ftrace_t *data)
{
    if (data->options.pid == -1 && execute_program(data))
        return 84;
    ptrace(PTRACE_ATTACH, data->options.pid, 0, 0);
    ptrace(PTRACE_SETOPTIONS, data->options.pid, 0, PTRACE_O_TRACESYSGOOD);

    int status;
    waitpid(data->options.pid, &status, 0);
    ptrace_getregs(data->options.pid, &data->regs);
    for (; status != -1 && (WIFSTOPPED(status) || WIFSIGNALED(status));
                        status = ptrace_singlestep(data->options.pid)) {
        if (trace_signals(status))
            continue;
        trace_execution(data, status);
    }
    ptrace(PTRACE_DETACH, data->options.pid, 0, 0);
    return 0;
}