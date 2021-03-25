/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:38:40 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/25 17:21:19 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int load_image(t_file *data)
{
    t_image *img;
    int has_move;
    t_point dir;

    img = &data->window.img;
    //TODO añadir comprobación por si no ha cambiado nada
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    move(data);
    print_map(data, img);
    draw_circle(data, img, data->gamer->position, 5, color_int(255, 0, 0));
    dir.x = data->gamer->position.x + data->gamer->direction.x;
    dir.y = data->gamer->position.y + data->gamer->direction.y;
    draw_circle(data, img, dir, 5, color_int(0, 255, 0));
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
    mlx_hook(data->window.win, EVENT_EXIT, 0, event_exit, data->gamer);
    mlx_loop_hook(data->window.ptr, load_image, data);
    mlx_loop(data->window.ptr);    
    return (0);
}