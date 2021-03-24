#include "cub3d.h"

int press_key_2(int keycode, t_gamer *gamer)
{
    printf("key: %d\n", keycode);
    return (0);
}
/*
void paint_map_antiguo(t_file *data)
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
    //draw_circle(mlx, win, data->gamer->position, 5, 0255000042);
    //draw_circle(mlx, win, data->gamer->direction, 5, 0000255000);
    mlx_hook(win, 2, 0, press_key_2, data->gamer);
    mlx_loop(mlx);
    
}
*/
int load_image(t_file *data)
{
    t_image *img;

    img = &data->window.img;
    
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    if (data->gamer->move.x == 1 && data->gamer->position.x + 5 < (double)data->width)
        data->gamer->position.x += 5;
    if (data->gamer->move.x == -1 && data->gamer->position.x - 5 > 0)
        data->gamer->position.x -= 5;
    print_map(data, img);
    draw_circle(data, img, data->gamer->position, 5, 0255000042);
    draw_circle(data, img, data->gamer->direction, 5, 0000255000);

    mlx_put_image_to_window(data->window.ptr, data->window.win, img->img, 0, 0);

    return (0);
}

int print_image(t_file *data)
{
    
    init_window(data);
    data->window.img.img = mlx_new_image(data->window.ptr, data->width, data->height);
    load_image(data);
    
    mlx_hook(data->window.win, 2, 0, &press_key_2, data->gamer);
    //mlx_hook(data->window.ptr, 3, 0, release_key, data->gamer);
    //mlx_loop_hook(data->window.ptr, load_image, data);
    mlx_loop(data->window.ptr);
    
    return (0);

}