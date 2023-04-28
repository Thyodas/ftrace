/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** nm.c
*/

#include <ctype.h>

#include "nm/nm.h"
#include "nm/data.h"
#include "nm/type.h"

static char *handle_elf(void *file, size_t size, u_int64_t address)
{
    switch (((Elf32_Ehdr *)file)->e_ident[EI_CLASS]) {
        case ELFCLASS64:
            return handle_elf_64(file, size, address);
    }
    return NULL;
}

static char *handle_ar(void *file, size_t size, u_int64_t address)
{
    ar_extract_t extract;
    if (extract_objects(&extract, file, size))
        return NULL;
    ar_obj_t *obj;
    char *name;
    for (size_t i = 0; i < extract.obj_list_len; ++i) {
        obj = &extract.obj_list[i];
        name = handle_elf((void *) obj->data, obj->data_len, address);
        if (name)
            return name;
    }
    free(extract.obj_list);
    return NULL;
}

static char *run_nm(void *file, size_t size, u_int64_t address)
{
    switch (get_file_type(file, size)) {
        case F_ELF:
            return handle_elf(file, size, address);
        case F_AR:
            return handle_ar(file, size, address);
        case F_ERROR:
            break;
    }
    fprintf(stderr, "%s: %s: file format not recognized\n", BIN, "nm");
    return NULL;
}

char *nm_get_symbol_name(char *path, u_int64_t address)
{
    int fd;
    struct stat s;
    void *file;
    if ((fd = open(path, O_RDONLY)) == -1 || fstat(fd, &s) == -1) {
        return NULL;
    }
    if ((file = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
        == MAP_FAILED) {
        close(fd);
        return NULL;
    }
    char *name = run_nm(file, s.st_size, address);
    close(fd);
    munmap(file, s.st_size);
    return name;
}
