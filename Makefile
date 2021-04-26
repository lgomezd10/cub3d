DIRLIBFT = libft

DIRMLX = mlx

MLX = mlx_linux/libmlx.a

LIBFT = ${DIRLIBFT}/libft.a

LIBMLX = libmlx.dylib

RM = rm -rf

CFLAGS = -O3 -g -Wall -Wextra -Werror -I.

FLAGSLIB = -Lmlx -lmlx -framework Metal -framework AppKit -lm

NAME = cub3D

NAMEBONUS = bonus

FILES = cub3d \
	utils/errors \
	utils/save_bmp \
	utils/utils_clear \
	utils/utils_draw \
	utils/utils_points \
	loadfile/load_map \
	loadfile/load_file \
	loadfile/load_file_utils \
	loadfile/load_player \
	loadfile/check_wall_closed \
	loadfile/check_wall_utils \
	game/game_utils \
	game/move_player \
	game/run_game \
	game/utils_hook \
	game/window \
	raycaster/raycaster_utils \
	raycaster/raycaster \
	sprites/list_sprite \
	sprites/sprites \

FILESBONUS = bonus/minimap \
	bonus/draw_minimap \
	bonus/game_bonus \
	bonus/utils_bonus \
	bonus/life \
	bonus/utils_life \
	bonus/collect_sprites

FBONUS = ${FILES} ${FILESBONUS}

SRC = ${addsuffix .c, ${addprefix src/, ${FILES}}}

SRCBONUS = ${addsuffix .c, ${addprefix src_bonus/, ${FBONUS}}}

OBJS = ${SRC:.c=.o}

OBJSBONUS = ${SRCBONUS:.c=.o}

${NAME} : ${LIBFT} ${LIBMLX} ${OBJS}
	gcc -g ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${LIBMLX} ${FLAGSLIB}

${NAMEBONUS} : ${LIBFT} ${LIBMLX} ${OBJSBONUS}
	gcc -g ${CFLAGS} -o ${NAME} ${OBJSBONUS} ${LIBFT} ${LIBMLX} ${FLAGSLIB}

all : ${NAME}

linux : ${LIBFT} ${OBJSBONUS} 
	clang -g -Wall -Wextra -Werror -lm -o ${NAME} ${OBJSBONUS}  ${LIBFT} ${MLX} -lbsd -lmlx -lXext -lX11

${LIBFT} :
		${MAKE} bonus -C ${DIRLIBFT}
${LIBMLX} : 
		${MAKE} -C mlx
		@cp ${DIRMLX}/${LIBMLX} .

clean:
	${RM} ${OBJS}
	${RM} ${OBJSBONUS}
	${MAKE} clean -C ${DIRMLX}
	${MAKE} fclean -C ${DIRLIBFT}

fclean:	clean
	${RM} ${NAME}
	${RM} ${LIBMLX}

re: fclean all

game1:	${NAMEBONUS}
	./cub3D maps/game1.cub
game2:	${NAMEBONUS}
	./cub3D maps/game200.cub maps/game201.cub maps/game202.cub maps/game203.cub

game2easy:	${NAMEBONUS}
	./cub3D maps/mapa0.cub maps/mapa1.cub