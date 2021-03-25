/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:38:40 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/24 17:38:46 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    int has_move;
    t_point dir;

    img = &data->window.img;
    
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    move(data);
    print_map(data, img);
    draw_circle(data, img, data->gamer->position, 5, 0255000042);
    dir.x = data->gamer->position.x + data->gamer->direction.x;
    dir.y = data->gamer->position.y + data->gamer->direction.y;
    draw_circle(data, img, dir, 5, 0000255000);

    mlx_put_image_to_window(data->window.ptr, data->window.win, img->img, 0, 0);

    return (0);
}

int print_image(t_file *data)
{
    
    init_window(data);

    data->window.img.img = mlx_new_image(data->window.ptr, data->width, data->height);
    load_image(data);
    
    mlx_hook(data->window.win, 2, 1L << 0, press_key, data->gamer);
    mlx_hook(data->window.win, 3, 1L << 1, release_key, data->gamer);
    mlx_loop_hook(data->window.ptr, load_image, data);
    mlx_loop(data->window.ptr);
    
    return (0);

}