/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** type.h
*/

#pragma once

#include <stddef.h>

typedef enum file_type_e {
    F_ERROR = -1,
    F_ELF = 0,
    F_AR = 1,
} file_type_t;

typedef struct {
    const char *name;
    const char *data;
    size_t name_len;
    size_t data_len;
} ar_obj_t;

typedef struct {
    ar_obj_t *obj_list;
    const char *string_table;
    size_t obj_list_len;
    size_t string_table_len;
} ar_extract_t;

// src/ar.c
int extract_objects(ar_extract_t *extract, void *file, size_t size);

// src/file.c
file_type_t get_file_type(void *file, size_t size);
