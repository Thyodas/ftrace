# Ftrace

Ftrace is a Unix system programming tool that allows you to analyze executables by tracing their system calls, internal function calls with names and addresses, signals received from other programs, and function calls contained in shared libraries (.so). It's similar to `strace`, but with additional functionality.

## Project Details

- **Binary Name**: ftrace
- **Language**: C
- **Compilation**: Via Makefile (supports commands like `make`, `make clean`, `make fclean`, `make re`)
- **Platform**: Developed for x86-64/Linux

## Project Features

### Traced Elements

Ftrace traces and displays the following elements of an executed program:

- **System Calls**: Lists system calls made by the program.
- **Internal Function Calls**: Shows the names and addresses of function calls within the program.
- **Signals**: Displays signals received from other programs.
- **Shared Libraries Functions**: Traces function calls from shared libraries (.so).

### Usage

You can use Ftrace to trace an executable as follows:

```bash
./ftrace ./a.out
```

### Error Handling

Error messages are written to the error output, and the program exits with an error code of 84 if an error occurs (or 0 if there is no error).

## Usage

You can use Ftrace to trace an executable by providing the command as follows:

```bash
./ftrace <command>
```

You can provide a binary as the command or directly a command in your PATH (e.g: ls)

You can also add the -s flag to show more details in syscalls (e.g.: show strings instead of address)

```bash
./ftrace -s <command>
```

## Example

Here's an example of Ftrace usage:

For this C program:

```C
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

```

```bash
$ ./ftrace -s ./a.out
Entering function main at 0x560a563e11c6
Entering function foo at 0x560a563e1194
Entering function bar at 0x560a563e1169
Entering function bar at 0x560a563e1169
Entering function bar at 0x560a563e1169
Entering function bar at 0x560a563e1169
Entering function bar at 0x560a563e1169
Entering function bar at 0x560a563e1169
Leaving function bar
Leaving function bar
Leaving function bar
Leaving function bar
Leaving function bar
Leaving function bar
 ...
Syscall write(1, "Hello world!\10", 13) = 13
 ...
Leaving function foo
Leaving function main
```

## Conclusion

Ftrace is a powerful tool for analyzing executables on Unix systems. It provides valuable insights into system calls, function calls, and signals, making it a valuable resource for debugging and understanding program behavior. Whether you use it for basic tracing or explore advanced features, Ftrace is a versatile tool for system programming.
