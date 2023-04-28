/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** type.c
*/

#include "nm/nm.h"
#include "nm/data.h"

static char get_data_type(data_64_t *data, Elf64_Sym *sym)
{
    switch (data->shdr[sym->st_shndx].sh_flags) {
        case (SHF_ALLOC | SHF_WRITE | SHF_TLS):
        case (SHF_ALLOC | SHF_WRITE):
            return 'D';
        case (SHF_ALLOC | SHF_EXECINSTR):
            return 'T';
        case 0:
            return '-';
    }
    return '?';
}

static char get_section_type(data_64_t *data, Elf64_Sym *sym)
{
    switch (data->shdr[sym->st_shndx].sh_type) {
        case SHT_NOBITS:
            if (data->shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
                return 'B';
            return '?';
        case SHT_PROGBITS:
            return get_data_type(data, sym);
        case SHT_FINI_ARRAY:
        case SHT_INIT_ARRAY:
        case SHT_DYNAMIC:
            return 'D';
    }
    return '?';
}

static char get_uppercase_type(data_64_t *data, Elf64_Sym *sym)
{
    if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        return 'u';
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
        if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
            return sym->st_shndx == SHN_UNDEF ? 'v' : 'V';
        else
            return sym->st_shndx == SHN_UNDEF ? 'w' : 'W';
    }
    switch (sym->st_shndx) {
        case SHN_ABS:
            return 'A';
        case SHN_COMMON:
            return 'C';
        case SHN_UNDEF:
            return 'U';
    }
    return get_section_type(data, sym);
}

char get_type_64(data_64_t *data, Elf64_Sym *sym)
{
    char type = get_uppercase_type(data, sym);
    if (type > 'a')
        return type;
    if (type == '?' && !(data->shdr[sym->st_shndx].sh_flags & SHF_WRITE))
        type = 'R';
    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && type != '?')
        type += 32;
    return type;
}
