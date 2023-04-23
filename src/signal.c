/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** signal.c
*/

#include "ftrace/signal.h"
#include <stdio.h>
#include <string.h>

void print_signals(int signum)
{
    const char *name = strsignal(signum);
    if (signum > 0 && signum < (int)SIGNAL_NB)
        name = signal_names[signum];
    if (name == NULL)
        name = "UNKNOWN";
    fprintf(stderr, "Received signal %s\n", name);
}
