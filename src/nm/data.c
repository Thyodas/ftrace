/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** data.c
*/

#include "nm/data.h"

int is_out_of_range_64(data_64_t *data, void *address)
{
    return (char *)address >= data->file_end;
}

char *handle_elf_64(void *file, size_t size, u_int64_t address)
{
    if (size < sizeof(Elf64_Ehdr))
        return NULL;
    data_64_t data = {.file = (char *)file, .file_end = (char *)file + size,
        .ehdr = (Elf64_Ehdr *)file, .sym_table = NULL, .sym_len = 0,
    };
    data.shdr = (Elf64_Shdr *)(file + data.ehdr->e_shoff);
    if (is_out_of_range_64(&data, data.shdr))
        return NULL;
    data.sh_strtab = &data.shdr[data.ehdr->e_shstrndx];
    if (is_out_of_range_64(&data, data.sh_strtab))
        return NULL;
    if (add_symbol_by_address_64(&data, address)) {
        return NULL;
    }
    if (data.sym_table == NULL || data.sym_len == 0) {
        return NULL;
    }
    free(data.sym_table);
    return strdup(data.sym_table[0].name);
}
