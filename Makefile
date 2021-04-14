DIR = ./libft

DIRMLX = mlx

MLX = mlx_linux/libmlx.a

LIBFT = ${DIR}/libft.a

LIBMLX = libmlx.dylib

FLAGS = -c -Wall -Wextra - Werror

NAME = cub3D

SRC = cub3d.c load_file.c ft_errors.c get_map.c utils_points.c\
ft_utils.c check_wall_closed.c run_game.c utils_draw.c window.c \
move.c utils_hook.c raycaster.c raycaster_utils.c list_sprite.c utils_clear.c sprites.c \
minimap.c game_utils.c save_bmp.c

CFLAGS = -O3 -Wall -Wextra -Werror -I.

FLAGSLIB = -Lmlx -lmlx -framework Metal -framework AppKit -lm

OBJS = ${SRC:.c=.o}

linux : ${LIBFT} ${OBJS}
	clang -g -Wall -Wextra -Werror -lm -o ${NAME} ${OBJS} ${LIBFT} ${MLX} -lbsd -lmlx -lXext -lX11

mac : ${LIBMLX} ${LIBFT} ${OBJS}
	gcc -g ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${FLAGSLIB}

all : ${NAME}

${LIBFT} :
		${MAKE} bonus -C ${DIR}
${LIBMLX} :
		${MAKE} -C mlx
		@cp ${DIRMLX}/${LIBMLX} .

clean:
	rm -rf ${NAME} *.o
	rm -rf ${DIR_MLX}/*.o
	rm -rf ${LIBMLX}