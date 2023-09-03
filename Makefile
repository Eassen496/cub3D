SRC		= 
OBJS	= ${SRC:.c=.o}
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
NAME	= cub3d

.c.o	:
	gcc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	: ${OBJS}
	gcc ${CFLAGS} main.c ${OBJS} -o ${NAME}

all		: ${NAME}

clean	:
	rm -rf ${OBJS}

fclean	: clean
	rm -rf ${NAME}

re		: fclean all

.PHONY	:	fclean clean re all
