/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** call_utils.c
*/

#include "ftrace/data.h"
#include "ftrace/ptrace.h"

/**
 * Return the offset to skip prefixes.
 * Prefixes are: REX, cs, ds, ss, es override, fs, gs, addr32, data16
 * override.
 * @param instruction The instruction to get the offset from
 * @return The offset to skip the prefixes
 */
static int skip_prefixes(instruction_t *instruction)
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
    u_int8_t reg = data->instruction.bytes[offset + 1] & 0x70;
    if (opcode == CALL_FF_OPCODE && (reg == 0x20 || reg == 0x30))
        return (data->regs.rip);
    return 0;
}

int is_function_return(ftrace_t *data)
{
    int opcode;
    size_t offset = skip_prefixes(&data->instruction);
    if (offset > sizeof(data->instruction.bytes) - 1)
        return 0;
    opcode = data->instruction.bytes[offset];
    return opcode == CALL_RET_C2_OPCODE || opcode == CALL_RET_C3_OPCODE
           || opcode == CALL_RET_CA_OPCODE || opcode == CALL_RET_CB_OPCODE;
}

/*for (int i = 0; i < 15; ++i)
fprintf(stderr, "%x ", data->instruction.bytes[i]);
fprintf(stderr, "\n");*/
u_int64_t get_plt_resolved_address(ftrace_t *data)
{
    int opcode;
    size_t offset = skip_prefixes(&data->instruction);
    if (offset > sizeof(data->instruction.bytes) - 1)
        return 0;
    opcode = data->instruction.bytes[offset];
    if (opcode == JMP_EB_OPCODE || opcode == JMP_E9_OPCODE
        || opcode == JMP_EA_OPCODE) {
        return (data->regs.rip);
    }
    if (offset > 14)
        return 0;
    u_int8_t reg = data->instruction.bytes[offset + 1] & 0x70;
    u_int8_t modrm = data->instruction.bytes[offset + 1];
    u_int8_t mod = modrm >> 6;
    u_int8_t rm = modrm & 0x7;
    if (opcode == JMP_FF_OPCODE && mod == 3 && (reg == 0x20 || reg == 0x30)
        && rm != 4 && rm != 5) {
        return (data->regs.rip);
    }
    return 0;
}
