SRC		= main.c get_next_line.c graphic.c
OBJS	= ${SRC:.c=.o}
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LIBMLX	= libmlx42.a
LIBGLFW	= -lglfw -L"/Users/abitonti/.brew/opt/glfw/lib/"
NAME	= cub3d

.c.o	:
	gcc ${CFLAGS} -c $< -o ${<:.c=.o}

all		: ${NAME}

${NAME}	: ${OBJS}
	gcc ${OBJS} ${LIBMLX} ${LIBGLFW} ${CFLAGS} -o ${NAME}

clean	:
	rm -rf ${OBJS}

fclean	: clean
	rm -rf ${NAME}

re		: fclean all

.PHONY	:	fclean clean re all
