/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:15:47 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 13:06:13 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/run_game.h"

int	move_one_side(t_game *data, t_point dir)
{
	double	new_x;
	double	new_y;

	data->has_moved = 1;
	new_x = data->player->pos.x + (dir.x * data->opt.mov_speed);
	new_y = data->player->pos.y + (dir.y * data->opt.mov_speed);
	if (in_space(data, new_x, new_y))
	{
		data->player->pos.y = new_y;
		data->player->pos.x = new_x;
		return (1);
	}
	return (0);
}

int	move_other_side(t_game *data, t_point dir)
{
	double	new_x;
	double	new_y;

	data->has_moved = 1;
	new_x = data->player->pos.x - (dir.x * data->opt.mov_speed);
	new_y = data->player->pos.y - (dir.y * data->opt.mov_speed);
	if (in_space(data, new_x, new_y))
	{
		data->player->pos.y = new_y;
		data->player->pos.x = new_x;
		return (1);
	}
	return (0);
}

void	rotate_dir(t_game *data)
{
	t_point	dir;
	t_point	plane;
	t_point	side;
	double	rot;

	data->has_moved = 1;
	rot = data->player->rotate * data->opt.rot_speed;
	data->has_moved = 1;
	dir = data->player->dir;
	plane = data->player->plane;
	side = data->player->dir_side;
	data->player->dir.x = dir.x * cos(rot) - dir.y * sin(rot);
	data->player->dir.y = dir.x * sin(rot) + dir.y * cos(rot);
	data->player->plane.x = plane.x * cos(rot) - plane.y * sin(rot);
	data->player->plane.y = plane.x * sin(rot) + plane.y * cos(rot);
	data->player->dir_side.x = side.x * cos(rot) - side.y * sin(rot);
	data->player->dir_side.y = side.x * sin(rot) + side.y * cos(rot);
}

int	move(t_game *data)
{
	t_player	*player;

	player = data->player;
	if (player->rotate)
		rotate_dir(data);
	if (player->move_in_side)
	{
		if (data->player->move_in_side == -1)
			move_one_side(data, player->dir_side);
		if (data->player->move_in_side == 1)
			move_other_side(data, player->dir_side);
	}
	if (player->move_in_dir)
	{
		if (player->move_in_dir == -1)
			move_one_side(data, player->dir);
		if (player->move_in_dir == 1)
			move_other_side(data, player->dir);
	}
	return (data->has_moved);
}
