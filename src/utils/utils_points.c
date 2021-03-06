/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 19:49:52 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/19 18:29:26 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_point(t_point *point, double x, double y)
{
	point->x = x;
	point->y = y;
}

void	copy_point(t_point *dest, t_point src)
{
	dest->x = src.x;
	dest->y = src.y;
}

void	set_point_int(t_point_int *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

int	valid_point(t_game *data, int x, int y)
{
	int		valid;
	t_table	table;

	table = data->table;
	valid = 0;
	valid = x >= 0 && x < table.cols;
	valid = valid && y >= 0 && y < table.rows;
	return (valid);
}

int	in_limits(t_point_int pos, t_point_int start, t_point_int end)
{
	int	valid;

	valid = 0;
	valid = pos.x >= start.x && pos.x < end.x;
	valid = valid && pos.y >= start.y && pos.y < end.y;
	return (valid);
}
