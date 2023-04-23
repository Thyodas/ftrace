/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ptrace.h
*/

#pragma once

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

void *ptrace_map_data(pid_t pid, unsigned long address, size_t size,
    size_t offset);
int ptrace_singlestep(pid_t pid);
int ptrace_getregs(int pid, struct user_regs_struct *regs);
