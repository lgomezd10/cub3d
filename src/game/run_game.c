/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:38:40 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/14 18:47:56 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/run_game.h"

int load_game(t_game *data)
{
    int ceiling;
    int floor;
    t_image *img;

    img = &data->window.img.img;
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    ceiling = color_int(data->ceiling->red, data->ceiling->green, data->ceiling->blue);
    floor = color_int(data->floor->red, data->floor->green, data->floor->blue);
    print_cel_floor(data, ceiling, floor, &data->window.img);

    return (0);
}

int load_image(t_game *data)
{
    static int firts_time = 1;
    t_image *img;

    if (data->window.win)
    {
        //mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->window.img.img.img);
        move(data);
        img = &data->window.img.img; 
        if (firts_time || data->has_moved)
        {
            data->has_moved = 0;            
            short_sprites(data);
            firts_time = 0;            
            load_game(data);
            raycaster(data);
            if (data->player->act_map)
                print_minimap(data);
           // mlx_do_sync(data->window.ptr);
        }
        mlx_put_image_to_window(data->window.ptr, data->window.win, img->img, 0, 0);
        if (data->to_save)
            save_bmp(data);
        
        //mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->window.win);
    }
    return (0);
}

int run_game(t_game *data)
{
    printf("to save vale %d\n", data->to_save);
    init_window(data);
    init_texture(data);    
    data->window.img.img.img = mlx_new_image(data->window.ptr, data->width, data->height);
    has_been_created(data->window.img.img.img);
    load_image(data);
    mlx_hook(data->window.win, 2, 1L << 0, press_key, data);
    mlx_hook(data->window.win, 3, 1L << 1, release_key, data);
    mlx_hook(data->window.win, EVENT_EXIT, 1L << 17, event_exit, data);
    mlx_loop_hook(data->window.ptr, load_image, data);
    mlx_loop(data->window.ptr);
    
    return (0);
}