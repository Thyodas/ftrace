##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC = src/main.c 							\
	  src/options.c							\
	  src/ftrace.c							\
	  src/permission.c						\
	  src/print.c							\
	  src/ptrace.c							\
	  src/signal.c							\

OBJ := $(SRC:.c=.o)

NAME := ftrace

INC = include
INC_PARAMS = $(INC:%=-I%)

CFLAGS = $(INC_PARAMS) -Wall -Wextra -g

%.o: %.c
	@echo "👉️ Compiling \033[1m$<\033[0m"
	@gcc $(CFLAGS) -c -o $@ $<

all:
	@$(MAKE) -s $(NAME)

title:
		@echo "\033[1;37m\033[1;46m                  ftrace\
                 \033[0m"

$(NAME): title $(OBJ)
		gcc -g -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: fclean title all re clean $(NAME)
