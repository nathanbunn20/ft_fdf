NAME	=	fdf
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRC		=	sources/fdf.c sources/filehandles.c sources/helpers.c \
			sources/drawingtools1_1.c sources/drawingtools2_1.c \
			sources/get_next_line.c sources/eventhandling.c \
			sources/morehelpers.c sources/point_handling.c \
			sources/camera.c
OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(CFLAGS) -I includes/ -I minilibx -L libft/ -lft -L minilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	mv helpers.o sources/
	mv fdf.o sources/
	mv filehandles.o sources/
	mv drawingtools1_1.o sources/
	mv drawingtools2_1.o sources/
	mv get_next_line.o sources/
	mv eventhandling.o sources/
	mv morehelpers.o sources/
	mv point_handling.o sources/
	mv camera.o sources/

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	rm -f libft/libft.a
	rm -f $(NAME)

re: fclean all
