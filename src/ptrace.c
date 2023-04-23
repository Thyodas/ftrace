/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ptrace.c
*/

#include "ftrace/ptrace.h"
#include "ftrace/data.h"

static void *ptrace_map_data_until_null(pid_t pid, unsigned long address,
    size_t offset)
{
    size_t i = 0;
    long word;
    void *data = NULL;
    void *off_data = malloc(offset);
    void *cmp_data = calloc(offset, 1);
    memset(off_data, 1, 1);
    do {
        word = ptrace(PTRACE_PEEKDATA, pid, address + i);
        data = realloc(data, i + 1);
        memset(data + i, (char)word, 1);
        ++i;
        if (i % offset == 0) {
            memmove(off_data, data + i - offset, offset);
        }
    } while ((i % offset != 0) || memcmp(off_data, cmp_data, offset) != 0);
    free(off_data);
    free(cmp_data);
    return data;
}

/**
 * Map data from pid to program.
 * Data will be malloced.
 * @param pid Pid of the child to trace.
 * @param address Address in the tracee to get data from.
 * @param size Size of the data (if 0, the function will get data until
 * NULL is reached according to offset).
 * @param offset Unused when size == 0.
 * Size of each part of the data to check for NULL.
 * e.g.: For a string, each part is a char (1 byte) so offset is 1.
 * @return The malloced mapped data from pid.
 */
void *ptrace_map_data(pid_t pid, unsigned long address, size_t size,
    size_t offset)
{
    void *data = NULL;
    size_t i = 0;
    long word;
    if (size == 0) {
        return ptrace_map_data_until_null(pid, address, offset);
    } else {
        data = malloc(size);
        do {
            word = ptrace(PTRACE_PEEKDATA, pid, address + i);
            memset(data + i, (char)word, 1);
            ++i;
        } while (i < size);
    }
    return data;
}

int ptrace_singlestep(pid_t pid)
{
    int status;
    if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) == -1) {
        return -1;
    }
    if (waitpid(pid, &status, 0) == -1)
        return -1;
    return status;
}

int ptrace_getregs(int pid, struct user_regs_struct *regs)
{
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) == -1) {
        return (84);
    }
    return 0;
}
