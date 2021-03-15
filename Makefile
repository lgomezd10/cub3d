DIR = ./libft

LIBFT = ${DIR}/libft.a

FLAGS = -c -Wall -Wextra - Werror

NAME = cub3d 

SRC = cub3d.c load_file.c ft_errors.c add_tolibft.c

OBJS = ${SRC:.c=.o}

linux : ${LIBFT} ${OBJS}
	clang -Wall -Wextra -Werror -o ${NAME} ${OBJS} ${LIBFT} -lbsd -lmlx -lXext -lX11

mac : ${OBJS}
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME} main2.c ${OBJS} ${LIBFT}

all : ${NAME}

${LIBFT} :
		${make} -C ${DIR}

clean:
	rm ${NAME} *.o