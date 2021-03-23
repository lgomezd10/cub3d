#include "cub3d.h"

int init_window(t_file *data)
{
    data->window.ptr = mlx_init();
    data->window.win = mlx_new_window(data->window.ptr, data->width, data->height, "CUB3D");
    return (0); 
}

void update_window(t_file *data)
{
    mlx_put_image_to_window(data->window.ptr, data->window.win, data->window.img.img, 0, 0);
}