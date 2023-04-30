/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** call.c
*/

#include "ftrace/data.h"
#include "ftrace/ptrace.h"

u_int64_t get_elf_address(ftrace_t *data, u_int64_t runtime_address,
    char *path);
char * nm_get_symbol_name(char *path, u_int64_t address);
u_int64_t get_call_address(ftrace_t *data);
int is_function_return(ftrace_t *data);
u_int64_t get_plt_resolved_address(ftrace_t *data);

int trace_plt_function(ftrace_t *data)
{
    data->last_was_plt_call = false;
    u_int64_t call = get_plt_resolved_address(data);
    u_int64_t static_address;
    char path[PATH_MAX + 1];
    char *name = NULL;
    if (call != 0) {
        static_address = get_elf_address(data, call, path);
        name = nm_get_symbol_name(path, static_address);
        if (name == NULL)
            name = nm_get_symbol_name(path, call);
    }
    vector_push_back(vectorize(&data->func_names), name);
    fprintf(stderr, "Entering function %s at %#lx\n",
        name ? name : "Unknown", call);
    return 1;
}

int trace_function(ftrace_t *data)
{
    if (data->last_was_plt_call)
        return trace_plt_function(data);
    u_int64_t call = get_call_address(data);
    u_int64_t static_address;
    char path[PATH_MAX + 1];
    char *name;
    if (call == 0)
        return 0;
    ++data->nb_call;
    static_address = get_elf_address(data, call, path);
    name = nm_get_symbol_name(path, static_address);
    if (name == NULL)
        name = nm_get_symbol_name(path, call);
    if (name == NULL) {
        data->last_was_plt_call = true;
        return 1;
    }
    vector_push_back(vectorize(&data->func_names), name);
    fprintf(stderr, "Entering function %s at %#lx\n",
        name ? name : "Unknown", call);
    return 1;
}

int trace_function_return(ftrace_t *data)
{
    if (!is_function_return(data)) {
        return 0;
    }
    ++data->nb_ret;
    char *name = vector_pop_back(vectorize(&data->func_names));
    fprintf(stderr, "Leaving function %s\n", name ? name : "Unknown");
    if (name)
        free(name);
    return 1;
}
