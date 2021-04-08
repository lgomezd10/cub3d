#include "cub3d.h"

void ft_errors(char *msg)
{
    perror(msg);
    exit(0);
}

void has_been_created(void *ptr)
{
    if (!ptr)
        ft_errors("Error al reservar");
}