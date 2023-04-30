/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** main.c
*/

#include "ftrace/data.h"

#include <stdio.h>
#include <string.h>

int start_ftrace(ftrace_t *data);

int main(int argc, char **argv)
{
    ftrace_t ftrace = {
        .options = {
            .detailed = false,
            .help = false,
            .command = NULL,
            .pid = -1,
        },
        .regs = {0}, .proc_maps = NULL, .nb_call = 0, .nb_ret = 0,
        .last_was_plt_call = false,
    };
    vector_init(vectorize(&ftrace.func_names), sizeof(string_t));
    if (parse_args(&ftrace.options, argc, argv))
        return 84;
    if (ftrace.options.help) {
        printf("USAGE: ./ftrace [-s] [-p <pid>|<command>]\n");
        return 0;
    }
    return start_ftrace(&ftrace);
}
