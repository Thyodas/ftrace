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

int find_static_symbol_by_address_64(data_64_t *data, u_int64_t address)
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

/*
int find_dyn_symbol_by_address_64(data_64_t *data, u_int64_t address)
{
    Elf64_Shdr *dynsym_tab = get_shdr_by_type_64(data, SHT_DYNSYM);
    if (dynsym_tab == NULL)
        return 1;
    Elf64_Shdr *dynsym_strtab = &data->shdr[dynsym_tab->sh_link];
    if (is_out_of_range_64(data, dynsym_strtab))
        return 1;
    Elf64_Sym *sym = (Elf64_Sym *) (data->file + dynsym_tab->sh_offset);
    char *str = (char *) (data->file + dynsym_strtab->sh_offset);
    if (is_out_of_range_64(data, sym) || is_out_of_range_64(data, str))
        return 1;
    for (Elf64_Word i = 1 ; i < dynsym_tab->sh_size / sizeof(Elf64_Sym) ; i++) {
        if (sym[i].st_value != address)
            continue;
        add_symbol_to_list(data, &sym[i], str + sym[i].st_name);
    }
    return 0;
}
*/

int find_dyn_symbol_by_address_64(data_64_t *data, u_int64_t address)
{
    Elf64_Shdr *rela_plt = get_shdr_by_name_64(data, ".rela.plt");
    if (rela_plt == NULL)
        return 1;
    Elf64_Rela *rela = (Elf64_Rela *) (data->file + rela_plt->sh_offset);
    Elf64_Shdr *dynsym = get_shdr_by_type_64(data, SHT_DYNSYM);
    if (dynsym == NULL) return 1;
    Elf64_Shdr *dynsym_strtab = &data->shdr[dynsym->sh_link];
    if (is_out_of_range_64(data, dynsym_strtab)) return 1;
    Elf64_Sym *sym = (Elf64_Sym *) (data->file + dynsym->sh_offset);
    char *str = (char *) (data->file + dynsym_strtab->sh_offset);
    if (is_out_of_range_64(data, sym) || is_out_of_range_64(data, str))
        return 1;
    for (Elf64_Word i = 0 ; i < rela_plt->sh_size / sizeof(Elf64_Rela) ; i++) {
        if (rela[i].r_offset == address) {
            Elf64_Word sym_index = ELF64_R_SYM(rela[i].r_info);
            add_symbol_to_list(data, &sym[sym_index],
                str + sym[sym_index].st_name);
        }
    }
    return 0;
}
