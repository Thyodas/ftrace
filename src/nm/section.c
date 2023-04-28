/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** section.c
*/

#include "nm/nm.h"
#include "nm/data.h"

Elf64_Shdr *get_shdr_by_type_64(data_64_t *data, Elf64_Word sh_type)
{
    int shnum = data->ehdr->e_shnum;

    for (int i = 0 ; i < shnum ; ++i) {
        if (is_out_of_range_64(data, &data->shdr[i]))
            return NULL;
        if (data->shdr[i].sh_type == sh_type)
            return &data->shdr[i];
    }
    return NULL;
}
