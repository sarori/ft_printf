# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sapark <sapark@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/24 17:01:45 by sapark            #+#    #+#              #
#    Updated: 2019/08/28 22:21:08 by sapark           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME=libftprintf.a

# SRC=$(wildcard src/*.c)
# CC=gcc -g -fsanitize=address
# CFLAGS=-Wall -Wextra -Werror -Iincludes
# OBJ = $(patsubst %.c, %.o, $(SRC))

# all: $(NAME)

# $(NAME): $(SRC)
# 	cd src/libft && make -f Makefile
# 	mv src/libft/libft.a .
# 	$(CC) -o $(NAME) $(CFLAGS) $(SRC) libft.a

# clean:
# 	-cd src/libft && make clean

# fclean: clean
# 	-cd src/libft && make fclean
# 	-rm -f $(NAME)
# 	-rm -f libft.a

# re: fclean $(NAME)

# .PHONY: clean fclean re

NAME=libftprintf.a

SRC=$(wildcard src/*.c)
LIBFT=lib/libft
LRC=$(wildcard $(LIBFT)/src/*.c)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iincludes
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
LOBJ = $(patsubst $(LIBFT)/src/%.c, $(LIBFT)/obj/%.o, $(LRC))

all: $(NAME)

$(NAME): obj $(OBJ)
	cd lib/libft && make pre
	ar rc $(NAME) $(OBJ) $(LOBJ)
	ranlib $(NAME)

obj:
	mkdir obj

obj/%.o: src/%.c
	gcc $(CFLAGS) $(OPTION) -c -o $@ $<

clean:
	-cd lib/libft && make clean
	-rm -rf obj

fclean: clean
	-rm -f $(NAME)
	-rm -f libft.a

re: fclean $(NAME)

.PHONY: clean fclean re
