DIR = ./libft

LIBFT = ${DIR}/libft.a

FLAGS = -c -Wall -Wextra - Werror

NAME = cub3d 

SRC = load_file.c ft_errors.c add_tolibft.c

OBJS = ${SRC:.c=.o}

linux : ${OBJS} ${LIBFT}
	clang -Wall -Wextra -Werror -o ${NAME} main3.c ${OBJS} ${LIBFT} -lbsd -lmlx -lXext -lX11

mac : ${OBJS}
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME} main2.c ${OBJS} ${LIBFT}

all : ${NAME}

${LIBFT} :
		${make} -C ${DIR}

clean:
	rm ${NAME}