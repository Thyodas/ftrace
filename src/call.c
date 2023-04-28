/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** call.c
*/

#include "ftrace/data.h"
#include "ftrace/ptrace.h"

u_int64_t get_static_address(ftrace_t *data, u_int64_t runtime_address,
    char *path);

char * nm_get_symbol_name(char *path, u_int64_t address);

/**
 * Return the offset to skip prefixes.
 * Prefixes are: REX, cs, ds, ss, es override, fs, gs, addr32, data16
 * override.
 * @param instruction The instruction to get the offset from
 * @return The offset to skip the prefixes
 */
int skip_prefixes(instruction_t *instruction)
{
    int offset = 0;
    for (; offset < (int)sizeof(instruction->bytes) && (
            (instruction->bytes[offset] & 0xe7) == 0x26
            || (instruction->bytes[offset] & 0xfc) == 0x64
            || (instruction->bytes[offset] & 0xf0) == 0x40);
        offset++);
    return offset;
}

u_int64_t get_call_address(ftrace_t *data)
{
    int opcode;
    size_t offset = skip_prefixes(&data->instruction);
    if (offset > sizeof(data->instruction.bytes) - 1)
        return 0;
    opcode = data->instruction.bytes[offset];
    if (opcode == CALL_E8_OPCODE) {
        return (data->regs.rip);
    }
    if (offset > 14)
        return 0;
    u_int8_t reg = data->instruction.bytes[offset + 1] & 0070;
    if (opcode == CALL_FF_OPCODE && (reg == 0020 || reg == 0030))
        return (data->regs.rip);
    return 0;
}

int trace_function(ftrace_t *data)
{
    u_int64_t call = get_call_address(data);
    u_int64_t static_address;
    char path[PATH_MAX + 1];
    char *name;
    if (call == 0)
        return 1;
    static_address = get_static_address(data, call, path);
    if (static_address == 0)
        return 1;
    name = nm_get_symbol_name(path, static_address);
    if (name == NULL)
        return 1;
    fprintf(stderr, "Entering function %s at %#lx\n",
        name, call);
    return 0;
}
