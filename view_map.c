/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:38:40 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/01 15:20:35 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int load_image(t_file *data)
{
    t_image *img;
    int has_move;
    t_point dir;
    t_point p1;
    t_point p2;
    int change;
    static int nofirts = 1;
    t_point pos;

    pos = data->gamer->position;
    img = &data->window.img;
    //TODO añadir comprobación por si no ha cambiado nada
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    change = move(data);
    if (nofirts || change)
    {
        nofirts = 0;
        print_map(data, img);    
        draw_circle(data, img, pos, 5, color_int(255, 0, 0));
        dir.x = pos.x + data->gamer->direction.x;
        dir.y = pos.y + data->gamer->direction.y;
        draw_circle(data, img, dir, 5, color_int(0, 255, 0));
        dir.x = pos.x + (data->gamer->direction.x * 10);
        dir.y = pos.y + (data->gamer->direction.y * 10);
        //draw_circle(data, img, dir, 5, color_int(0, 255, 0));
        //print_line(data, data->gamer->position, dir, color_int(0, 0, 255), img);
        view_game(data);
        mlx_put_image_to_window(data->window.ptr, data->window.win, img->img, 0, 0);
    }
    return (0);
}

int print_image(t_file *data)
{    
    init_window(data);
    data->window.img.img = mlx_new_image(data->window.ptr, data->width, data->height);
    load_image(data);    
    mlx_hook(data->window.win, 2, 1L << 0, press_key, data->gamer);
    mlx_hook(data->window.win, 3, 1L << 1, release_key, data->gamer);
    mlx_hook(data->window.win, EVENT_EXIT, 0, event_exit, data->gamer);
    mlx_loop_hook(data->window.ptr, load_image, data);
    mlx_loop(data->window.ptr);    
    return (0);
}