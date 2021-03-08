NAME = cub3d
${NAME} : 
	clang -Wall -Wextra -Werror -o ${NAME} main3.c -lbsd -lmlx -lXext -lX11
all : ${NAME}
clean:
	rm ${NAME}