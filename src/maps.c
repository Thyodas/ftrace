/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** maps.c
*/

#include "ftrace/data.h"
#include "ftrace/ptrace.h"
#include <stdio.h>

/*
 * This function horrendously reopen the file each time since
 * rewind doesn't work as intended? Why I don't know
 * I've suffered enough lol
 */
static int open_proc_maps(ftrace_t *data)
{
    if (data->proc_maps != NULL)
        fclose(data->proc_maps);
    char path[strlen("/proc//maps") + strlen("32768")];
    if (sprintf(path, "/proc/%d/maps", data->options.pid) < 0)
        return 1;
    data->proc_maps = fopen(path, "rb");
    if (data->proc_maps == NULL)
        return 1;
    return 0;
}

u_int64_t get_elf_address(ftrace_t *data, u_int64_t runtime_address,
    char *path)
{
    if (open_proc_maps(data))
        return 0;
    u_int64_t lower_bound, upper_bound, offset;
    char line[4096];
    char *out;
    int x;
    while ((out = fgets(line, 4095, data->proc_maps)) != NULL) {
        x = sscanf(line, "%lx-%lx %*s %lx %*s %*s %"
            STR(PATH_MAX) "s", &lower_bound, &upper_bound, &offset, path);
        if (x != 3 && x != 4) {
            return 0;
        }
        if (runtime_address >= lower_bound && runtime_address < upper_bound) {
            return (runtime_address - lower_bound + offset);
        }
    }
    return 0;
}
