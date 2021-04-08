/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:38:40 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/08 19:19:22 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int load_game(t_file *data)
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

int load_map(t_file *data)
{
    t_image *img;
    int has_move;
    t_point dir;
    t_point p1;
    t_point p2;    
    t_point pos;

    pos = data->gamer->pos;
    img = &data->map.img;
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    print_map(data, &data->map);
    draw_circle(data, &data->map, pos, 5, color_int(255, 0, 0));
    dir.x = pos.x + data->gamer->dir.x;
    dir.y = pos.y + data->gamer->dir.y;
    draw_circle(data, &data->map, dir, 5, color_int(0, 255, 0));
    dir.x = pos.x + (data->gamer->dir.x * 10);
    dir.y = pos.y + (data->gamer->dir.y * 10);
    //draw_circle(data, img, dir, 5, color_int(0, 255, 0));
    //print_line(data, data->gamer->pos, dir, color_int(0, 0, 255), img);
    
    return (0);
}
int load_image(t_file *data)
{

    int change;
    static int nofirts = 1;
    t_image *img;
    t_image *map;
    int init;

    // TODO: controlar que el mapa no sea menor de 300
    /*
    if (data->closed)
    {
        printf("Se van a borrar los datos");
        clear_window(data);
        printf("Se han borrado los datos");
        exit(0);
    }
    */
    if (data->window.win)
    {
        change = move(data);
        img = &data->window.img.img;
        map = &data->map.img;    
        if (nofirts || change)
        {
            if (!nofirts && img->img)
            { 
                mlx_destroy_image(data->window.ptr, img->img);
                //img->img = 0;
                img->img = mlx_new_image(data->window.ptr, data->width, data->height);
                has_been_created(img->img);                          
            }
            
            short_sprites(data);
            
            nofirts = 0;
            if (data->gamer->act_map)
                load_map(data);
            load_game(data);
            raycaster(data);
            
            //mlx_put_image_to_window(data->window.ptr, data->window.win, data->text[North].img.img, 0, 0);
        }
        mlx_put_image_to_window(data->window.ptr, data->window.win, img->img, 0, 0);
        if (data->gamer->act_map)
            mlx_put_image_to_window(data->window.ptr, data->window.win, map->img, data->map.init.x, data->map.init.y);
    }
    return (0);
}

int print_image(t_file *data)
{
    init_window(data);
    init_texture(data);    
    data->window.img.img.img = mlx_new_image(data->window.ptr, data->width, data->height);
    has_been_created(data->window.img.img.img);
    data->map.img.img = mlx_new_image(data->window.ptr, data->map.width, data->map.height);
    has_been_created(data->window.img.img.img);
    load_image(data);    
    mlx_hook(data->window.win, 2, 1L << 0, press_key, data->gamer);
    mlx_hook(data->window.win, 3, 1L << 1, release_key, data->gamer);
    mlx_hook(data->window.win, EVENT_EXIT, 1L << 17, event_exit, data);
    mlx_loop_hook(data->window.ptr, load_image, data);
    mlx_loop(data->window.ptr);
    return (0);
}