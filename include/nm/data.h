/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** data.h
*/

#pragma once

#include "nm.h"
#include "symbol.h"

typedef struct data_64_s {
    char *file;
    char *file_end;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    Elf64_Shdr *sh_strtab;
    sym_64_t *sym_table;
    size_t sym_len;
} data_64_t;

// src/64/data.c
char *handle_elf_64(void *file, size_t size, u_int64_t address);
int is_out_of_range_64(data_64_t *data, void *address);
