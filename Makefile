NAME = cub3d
linux : 
	clang -Wall -Wextra -Werror -o ${NAME} main3.c -lbsd -lmlx -lXext -lX11
mac : 
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME} main2.c
all : ${NAME}
clean:
	rm ${NAME}