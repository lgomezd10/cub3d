/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:15:31 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/27 17:56:59 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

t_point	pos_in_minimap(t_game *data, t_point src)
{
	t_point	pos;

	pos.x = (src.x - data->minimap.init_table.x) * data->minimap.unit_width;
	pos.x += data->minimap.init.x;
	pos.y = (src.y - data->minimap.init_table.y) * data->minimap.unit_height;
	pos.y += data->minimap.init.y;
	return (pos);
}

void	draw_triangle(t_game *data, int size, int color)
{
	t_player	*player;
	t_point		pos;
	t_point_int	draw;
	t_point_int	add;
	int			sizey;

	player = data->player;
	pos = pos_in_minimap(data, player->pos);
	add.x = 0;
	sizey = size;
	while (sizey > 0)
	{
		add.y = -sizey;
		while (add.y <= sizey)
		{
			draw.x = pos.x + (add.y * player->dir_side.x);
			draw.y = pos.y + (add.y * player->dir_side.y);
			my_mlx_pixel_put(&data->window.img, draw.x, draw.y, color);
			add.y++;
		}
		sizey--;
		add.x++;
		pos.x = pos.x + (player->dir.x);
		pos.y = pos.y + (player->dir.y);
	}
}

void	draw_circle_map(t_game *data, t_point center, double radius, int color)
{
	int		i;
	int		j;
	int		to_y;
	int		to_x;
	t_point	point;

	center = pos_in_minimap(data, center);
	i = center.y - radius;
	to_y = i + (2 * radius);
	while (i <= to_y)
	{
		j = center.x - radius;
		to_x = j + (2 * radius);
		while (j <= to_x)
		{
			point.x = j;
			point.y = i;
			if (is_in_radius(point, center, radius))
				my_mlx_pixel_put(&data->window.img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_sprites(t_game *data)
{
	t_sprite	*list;
	t_minimap	map;
	t_point_int	pos;

	map = data->minimap;
	list = data->sprites.begin;
	while (list)
	{
		pos.x = list->pos.x;
		pos.y = list->pos.y;
		if (!data->minimap.size_map
			|| in_limits(pos, map.init_table, map.end_table))
			draw_circle_map(data, list->pos, 8, data->minimap.color_sprites);
		list = list->next;
	}
}
