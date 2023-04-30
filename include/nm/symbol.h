/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** symbol.h
*/

#pragma once

typedef struct data_64_s data_64_t;

typedef struct {
    Elf64_Sym *sym;
    Elf64_Addr value;
    char type;
    char *name;
} sym_64_t;

// src/64/symbol/symbol.c
int find_static_symbol_by_address_64(data_64_t *data, u_int64_t address);
int find_dyn_symbol_by_address_64(data_64_t *data, u_int64_t address);

int cmp_symbol_64(const void *a, const void *b);
void print_all_symbols_64(data_64_t *data);

// src/64/symbol/type.c
char get_type_64(data_64_t *data, Elf64_Sym *sym);
