/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:35:24 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/22 18:34:30 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/run_game.h"

int	is_in_radius(t_point point, t_point center, double radius)
{
	t_point	power;
	double	distance;

	power.x = (point.x - center.x) * (point.x - center.x);
	power.y = (point.y - center.y) * (point.y - center.y);
	distance = sqrt(power.x + power.y);
	return (distance <= radius);
}

int	hit_sprite(t_game *data, double x, double y)
{
	t_point	center;
	t_point	point;
	int		i;
	int		j;

	i = (int)y;
	j = (int)x;
	if (data->table.table[i][j] == '2')
	{
		center.x = j + 0.5;
		center.y = i + 0.5;
		point.x = x;
		point.y = y;
		if (is_in_radius(point, center, 0.8))
		{
			sprite_found(data, j, i);
			return (1);
		}
	}
	return (0);
}

int	in_space(t_game *data, double x, double y)
{
	int	i;
	int	j;
	int	is_space;

	i = (int)y;
	j = (int)x;
	is_space = y >= 0 && i < data->table.rows;
	is_space = is_space && x >= 0 && j < data->table.cols;
	is_space = is_space && data->table.table[i][j] != '1';
	is_space = is_space && !hit_sprite(data, x, y);
	return (is_space);
}

int	in_space_int(t_game *data, int x, int y)
{	
	int	is_space;

	is_space = y >= 0 && y < data->table.rows;
	is_space = is_space && x >= 0 && x < data->table.cols;
	is_space = is_space && data->table.table[y][x] != '1';
	return (is_space);
}
