/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** section.h
*/

#pragma once

#include "nm.h"
#include "data.h"

// src/64/section.c
Elf64_Shdr *get_shdr_by_type_64(data_64_t *data, Elf64_Word sh_type);
Elf64_Shdr *get_shdr_by_name_64(data_64_t *data, const char *name);
