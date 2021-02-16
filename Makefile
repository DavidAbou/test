##
## EPITECH PROJECT, 2021
## my_sokoban
## File description:
## Makefile
##

SRC	=	sokoban.c

NAME	=	my_sokoban

all:
	gcc $(SRC) -o $(NAME) -lncurses -Wall

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all