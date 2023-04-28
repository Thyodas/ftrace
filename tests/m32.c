/*
** EPITECH PROJECT, 2023
** nmobjdump
** File description:
** m32.c
*/

#include <stdio.h>
#include <unistd.h>

int bar(int i)
{
    if (i <= 0)
        return 1;
    return bar(i - 1);
}

int foo(void)
{
    bar(5);
    puts("Hello world!\n");
    sleep(2);
    return 0;
}

int main()
{
    return foo();
}
