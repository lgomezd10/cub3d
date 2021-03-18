DIR = ./libft

LIBFT = ${DIR}/libft.a

FLAGS = -c -Wall -Wextra - Werror

NAME = cub3d 

SRC = cub3d.c load_file.c ft_errors.c add_tolibft.c get_map.c \
ft_utils.c check_map.c

OBJS = ${SRC:.c=.o}

${LIBFT} :
		${MAKE} bonus -C ${DIR}

linux : ${LIBFT} ${OBJS}
	clang -Wall -Wextra -Werror -o ${NAME} ${OBJS} ${LIBFT} -lbsd -lmlx -lXext -lX11

mac : ${LIBFT} ${OBJS}
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME} ${OBJS} ${LIBFT}

all : ${NAME}

clean:
	rm ${NAME} *.o