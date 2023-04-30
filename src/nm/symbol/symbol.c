/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** symbol.c
*/

#include "nm/nm.h"
#include "nm/section.h"
#include "nm/symbol.h"

int cmp_symbol_64(const void *a, const void *b)
{
    const sym_64_t *sym_a = a;
    const sym_64_t *sym_b = b;
    return strcmp(sym_a->name, sym_b->name);
}

static void add_symbol_to_list(data_64_t *data, Elf64_Sym *sym, char *name)
{
    if (ELF64_ST_TYPE(sym->st_info) == STT_SECTION ||
        ELF64_ST_TYPE(sym->st_info) == STT_FILE)
        return;
    data->sym_table = realloc(data->sym_table,
        sizeof(sym_64_t) * (data->sym_len + 1));
    data->sym_table[data->sym_len] = (sym_64_t) {
        .value = sym->st_value,
        .type = get_type_64(data, sym),
        .name = name,
        .sym = sym,
    };
    ++data->sym_len;
}

int add_symbol_by_address_64(data_64_t *data, u_int64_t address)
{
    Elf64_Shdr *symtab = get_shdr_by_type_64(data, SHT_SYMTAB);
    if (symtab == NULL)
        return 1;
    Elf64_Shdr *strtab = &data->shdr[symtab->sh_link];
    if (is_out_of_range_64(data, strtab))
        return 1;
    Elf64_Sym *sym = (Elf64_Sym *) (data->file + symtab->sh_offset);
    char *str = (char *) (data->file + strtab->sh_offset);
    if (is_out_of_range_64(data, sym) || is_out_of_range_64(data, str))
        return 1;
    for (Elf64_Word i = 1 ; i < symtab->sh_size / sizeof(Elf64_Sym) ; i++) {
        if (sym[i].st_value != address)
            continue;
        add_symbol_to_list(data, &sym[i], str + sym[i].st_name);
    }
    return 0;
}

void print_all_symbols_64(data_64_t *data)
{
    for (size_t i = 0 ; i < data->sym_len ; ++i) {
        if (data->sym_table[i].sym->st_shndx == SHN_UNDEF)
            printf("                 %c %s\n", data->sym_table[i].type,
                data->sym_table[i].name);
        else
            printf("%016lx %c %s\n", data->sym_table[i].value,
                data->sym_table[i].type, data->sym_table[i].name);
    }
}
