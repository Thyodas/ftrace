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
	  src/call.c							\
	  src/call_utils.c						\
	  src/maps.c							\
	  src/nm/nm.c							\
	  src/nm/data.c							\
	  src/nm/section.c						\
	  src/nm/symbol/symbol.c				\
	  src/nm/symbol/type.c					\
	  src/nm/ar.c							\
	  src/nm/file.c							\
	  src/vector/element.c					\
	  src/vector/init.c						\
	  src/vector/save.c						\

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

tests_run:
	./tests/test.sh


.PHONY: fclean title all re clean tests_run $(NAME)
