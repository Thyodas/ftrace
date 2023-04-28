/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** ar.c
*/

#include "nm/type.h"

#include <ar.h>
#include <stdlib.h>
#include <string.h>

static int set_string_table(ar_extract_t *extract, void *file, size_t size)
{
    size_t obj_size;
    for (struct ar_hdr *header = (struct ar_hdr *)(file + SARMAG);
        header < (struct ar_hdr *)(file + size);
        header = (struct ar_hdr *)
            ((char *) header + obj_size + sizeof(struct ar_hdr))) {
        if (strncmp(header->ar_fmag, ARFMAG, 2) != 0)
            return 1;
        obj_size = strtol(header->ar_size, NULL, 10);
        if (strncmp(header->ar_name, "//", 2) == 0) {
            extract->string_table = (char *)header + sizeof(struct ar_hdr);
            extract->string_table_len = obj_size;
            return 0;
        }
    }
    return 0;
}

static int init_ar_extract(ar_extract_t *extract, void *file, size_t size)
{
    *extract = (ar_extract_t){
        .obj_list = NULL,
        .obj_list_len = 0,
        .string_table = NULL,
        .string_table_len = 0,
    };
    return set_string_table(extract, file, size);
}

static int is_object_valid(struct ar_hdr *header)
{
    if (strncmp(header->ar_name, "/ ", 2) == 0
        || strncmp(header->ar_name, "//", 2) == 0
        || strncmp(header->ar_name, "/SYM64/", 7) == 0)
        return 0;
    if (get_file_type((char *)header + sizeof(struct ar_hdr),
        strtol(header->ar_size, NULL, 10)) != F_ELF)
        return 0;
    return 1;
}

static int add_object(ar_extract_t *extract, struct ar_hdr *header)
{
    extract->obj_list = realloc(extract->obj_list,
        sizeof(ar_obj_t) * (extract->obj_list_len + 1));
    ar_obj_t *obj = &extract->obj_list[extract->obj_list_len++];
    if (header->ar_name[0] == '/') {
        size_t pos = strtol(header->ar_name + 1, NULL, 10);
        if (extract->string_table_len == 0 || pos >= extract->string_table_len)
            return 1;
        obj->name = extract->string_table + pos;
    } else {
        obj->name = header->ar_name;
    }
    char *slash_pos = strchr(obj->name, '/');
    if (slash_pos == NULL)
        return 1;
    obj->name_len = slash_pos - obj->name;
    obj->data = (char *)header + sizeof(struct ar_hdr);
    obj->data_len = strtol(header->ar_size, NULL, 10);
    return 0;
}

int extract_objects(ar_extract_t *extract, void *file, size_t size)
{
    if (init_ar_extract(extract, file, size))
        return 1;
    size_t obj_size;
    for (struct ar_hdr *header = (struct ar_hdr *)(file + SARMAG);
        header < (struct ar_hdr *)(file + size);
        header = (struct ar_hdr *)
            ((char *) header + obj_size + sizeof(struct ar_hdr))) {
        if (strncmp(header->ar_fmag, ARFMAG, 2) != 0)
            return 1;
        obj_size = strtol(header->ar_size, NULL, 10);
        if (!is_object_valid(header))
            continue;
        if (add_object(extract, header))
            return 1;
    }
    return 0;
}
