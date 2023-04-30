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

#define CALL_E8_OPCODE 0xe8
#define CALL_FF_OPCODE 0xff
#define CALL_9A_OPCODE 0x9a

#define CALL_RET_C3_OPCODE 0xc3
#define CALL_RET_CB_OPCODE 0xcb
#define CALL_RET_C2_OPCODE 0xc2
#define CALL_RET_CA_OPCODE 0xca

#define SYSCALL_OPCODE 0x050f

#define GET_OPCODE(value) (value & 0xff)

void *ptrace_map_data(pid_t pid, unsigned long address, size_t size,
    size_t offset);
int ptrace_singlestep(pid_t pid);
int ptrace_getregs(int pid, struct user_regs_struct *regs);
