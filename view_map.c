#include "cub3d.h"

int press_key(int keycode, t_gamer *gamer)
{
    printf("key: %d", keycode);
}

void paint_map(t_file *data)
{
    void *mlx;
    void *win;
    int unitWidth;
    int unitHeight;
    int unit;
    int i;
    int j;
    int x;
    int y;

    mlx = mlx_init();
    
    win = mlx_new_window(mlx, data->width, data->height, "CUB3D");    
    unitWidth = 600 / data->table->cols;
    unitHeight = 600 / data->table->rows;

    i = 0;    
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {        
           //y = i / unitHeight;
           //x = j / unitWidth;
        
           y = i / data->gamer->unitHeight;
           x = j / data->gamer->unitWidth;
           if (data->table->table[y][x] == '1')
            mlx_pixel_put(mlx, win, j, i, 0255255255);
           j++;
        }
        i++;
    }
    printf("pos y: %f, pos x: %f\n", data->gamer->position.y, data->gamer->position.x);
    mlx_pixel_put(mlx, win, data->gamer->position.x, data->gamer->position.y, 0255000042);
    mlx_pixel_put(mlx, win, data->gamer->direction.x, data->gamer->direction.y, 0255000042);    
    draw_circle(mlx, win, data->gamer->position, 5, 0255000042);
    draw_circle(mlx, win, data->gamer->direction, 5, 0000255000);
    //mlx_hook(win, 2, 0, press_key, data->gamer);
    mlx_loop(mlx);
    
}