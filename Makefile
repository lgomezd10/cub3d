DIR = ./libft

DIRMLX = mlx

MLX = mlx_linux/libmlx.a

LIBFT = ${DIR}/libft.a

LIBMLX = libmlx.dylib

FLAGS = -c -Wall -Wextra - Werror

NAME = cub3D

MAIN = cub3d.c

FILES = utils/errors \
	utils/save_bmp \
	utils/utils_clear \
	utils/utils_draw \
	utils/utils_points \
	loadfile/load_map \
	loadfile/load_file \
	loadfile/load_player \
	loadfile/check_wall_closed \
	game/game_utils \
	game/move_player \
	game/run_game \
	game/utils_hook \
	game/window \
	raycaster/raycaster_utils \
	raycaster/raycaster \
	sprites/list_sprite \
	sprites/sprites \

FBONUS = bonus/minimap

SRCFILES = ${addsuffix .c, ${addprefix src/, ${FILES}}}

SRCBONUS = ${addsuffix .c, ${addprefix src/, ${FBONUS}}}

SRC = ${MAIN} ${SRCFILES} ${SRCBONUS}

CFLAGS = -O3 -g -Wall -Wextra -Werror -I.

FLAGSLIB = -Lmlx -lmlx -framework Metal -framework AppKit -lm

OBJS = ${SRC:.c=.o}

linux : ${LIBFT} ${OBJS} 
	clang -g -Wall -Wextra -Werror -lm -o ${NAME} ${OBJS}  ${LIBFT} ${MLX} -lbsd -lmlx -lXext -lX11

mac : ${LIBMLX} ${LIBFT} ${OBJS}
	gcc -g ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${FLAGSLIB}

all : ${NAME}

${LIBFT} :
		${MAKE} bonus -C ${DIR}
${LIBMLX} :
		${MAKE} -C mlx
		@cp ${DIRMLX}/${LIBMLX} .

clean:
	rm -rf ${OBJS}
	rm -rf ${NAME} *.o
	rm -rf ${DIR_MLX}/*.o
	rm -rf ${LIBMLX}