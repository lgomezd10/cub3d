#include "cub3d.h"

int init_window(t_file *data)
{
    int init;
    /*
    data->opt.mov_speed = 0.11;
    data->opt.rot_speed = 0.11;
    data->map.height = data->height / 3 - 10;
    data->map.width = data->width - 10;
    data->map.unitHeight = data->map.height / data->table->rows;
    data->map.unitWidth = data->map.width / data->table->cols;
    */
    
    data->opt.mov_speed = 0.11;
    data->opt.rot_speed = 0.11;
    data->map.height = (data->height / 3);
    data->map.width = (data->width / 3);
    data->map.unitHeight = data->map.height / data->table->rows;
    data->map.unitWidth = data->map.width / data->table->cols;
    init = ((data->width / 3) * 2) - 1;    
    set_point_int(&data->map.init, init, 0);
    data->window.img.height = data->height;
    data->window.img.width = data->width;
    data->window.img.unitHeight = data->window.img.height / data->table->rows;
    data->window.img.unitWidth = data->window.img.width / data->table->cols;
    set_point_int(&data->window.img.init, 0, 0);
    data->window.ptr = mlx_init();
    data->window.win = mlx_new_window(data->window.ptr, data->width, data->height, "CUB3D");
    printf("iniciada venta\n");
    return (0); 
}