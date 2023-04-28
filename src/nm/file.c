/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** file.c
*/

#include "nm/type.h"

#include <ar.h>
#include <elf.h>
#include <memory.h>

file_type_t get_file_type(void *file, size_t size)
{
    if (size >= SELFMAG && memcmp(file, ELFMAG, SELFMAG) == 0)
        return F_ELF;
    if (size >= SARMAG && memcmp(file, ARMAG, SARMAG) == 0)
        return F_AR;
    return F_ERROR;
}
