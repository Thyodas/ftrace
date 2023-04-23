/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** options.c
*/

#include "ftrace/options.h"

static int handle_option_pid(ftrace_options_t *options)
{
    char *next;
    long val = strtol(optarg, &next, 10);
    if (*next != '\0' || val > INT_MAX || val < 0) {
        fprintf(stderr, "ftrace: Invalid process id: '%s'\n",
            optarg);
        return 84;
    }
    options->pid = (int)val;
    return 0;
}

static int handle_option(ftrace_options_t *options, int getopt_output)
{
    switch (getopt_output) {
        case 's':
            options->detailed = true;
            return 0;
        case 'h':
            options->help = true;
            return 0;
        case 'p':
            return handle_option_pid(options);
        default:
            fprintf(stdout, "Try 'ftrace -h' for more information.\n");
            return 84;
    }
    return 0;
}

int parse_args(ftrace_options_t *options, int argc, char **argv)
{
    int output;
    static struct option long_options[] = {{"help", no_argument, 0, 'h'},
        {"pid", required_argument, 0, 'p'},
        {"detailed", no_argument, 0, 's'},
        {0, 0, 0, 0}
    };
    while ((output =
        getopt_long(argc, argv, "+shp:", long_options, NULL)) != -1) {
        if (handle_option(options, output))
            return 84;
    }
    if ((options->pid != -1 && optind < argc)
        || (options->pid == -1 && optind == argc)) {
        fprintf(stderr, "ftrace: must have PROG [ARGS] or -p PID\n");
        fprintf(stdout, "Try 'ftrace -h' for more information.\n");
        return 84;
    }
    if (options->pid == -1)
        options->command = (const char *const *)&argv[optind];
    return 0;
}
