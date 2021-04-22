/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:40:22 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/22 15:43:13 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

void draw_rectangle(t_game *data, t_point_int start, t_point_int end, int color)
{
    int x;
    int y;

    y = start.y;
    while (y < end.y)
    {
        x = start.x;
        while (x < end.x)
        {
            my_mlx_pixel_put(&data->window.img, x, y, color);
            x++;
        }
        y++;
    }
    
}