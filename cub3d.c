#include "cub3d.h"

int main(int argc, char **argv)
{
    int fd;
    t_file data;

    ft_bzero(&data, sizeof(t_file));
    if (argc < 2 || argc > 3)
        ft_errors("Solo se permiten dos argumentos");
    else
    {
        load_file(argv[1], &data);
    }
}