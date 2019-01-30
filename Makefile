##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## infin_add
##

NAME	=		my_hunter

SRC		=		src/jeu.c				\
				src/1fonction.c			\
				src/fonction2.c			\
				src/moveimage.c

OBJ		=		$(SRC:.c=.o)

all:	$(NAME)

$(NAME):		$(OBJ)
		gcc -o $(NAME) $(OBJ) -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

tests_run:
		gcc -o test ../tests/testct.c cat.c -lcriterion
		./test