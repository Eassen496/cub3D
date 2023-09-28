SRC		= main.c ./src/get_next_line.c ./src/graphic1.c ./src/graphic2.c ./src/graphic3.c ./src/graphic4.c\
		./src/control.c ./src/fill.c ./src/map.c ./src/struct.c ./src/utils1.c src/struct2.c\
		./src/utils2.c ./src/utils3.c ./src/utils4.c ./src/fill2.c
OBJS	= ${SRC:.c=.o}
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LIBMLX	= ./MLX42/build/libmlx42.a
LIBGLFW	= -lglfw -L"/Users/${USER}/.brew/opt/glfw/lib/"
NAME	= cub3d

.c.o	:
	gcc ${CFLAGS} -c $< -o ${<:.c=.o}

all		: 
	make setup
	make -C ./MLX42/build
	make cube

cube	: ${NAME}

setup	:
	$(shell mkdir MLX42/build &>/dev/null)
	$(shell cmake -S ./MLX42 -B ./MLX42/build &>/dev/null)
	@echo "setup complete"

rebuild	:
	@rm -rf ./MLX42/build
	@echo "rebuilding source..."
	make setup

basic	:
	@rm -rf ./MLX42/build

${NAME}	: ${OBJS}
	gcc ${OBJS} ${LIBMLX} ${LIBGLFW} ${CFLAGS} -o ${NAME}

clean	:
	rm -rf ${OBJS}
	make clean -C ./MLX42/build

fclean	: clean
	@make basic
	rm -rf ${NAME}

re		: fclean all

.PHONY	:	fclean clean re all
