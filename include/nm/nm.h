/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** nm.h
*/

#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ar.h>

#define BIN "nm"

// src/nm.c
int handle_files(int argc, char **argv);
