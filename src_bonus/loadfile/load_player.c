/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:18:02 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 14:19:28 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_dir_and_plane(t_game *data, t_player *player)
{
	if (data->player_init == 'N')
	{
		set_point(&player->dir, 0, -1);
		set_point(&player->dir_side, 1, 0);
		set_point(&player->plane, 0.66, 0.0);
	}
	if (data->player_init == 'S')
	{
		set_point(&player->dir, 0, 1);
		set_point(&player->dir_side, -1, 0);
		set_point(&player->plane, -0.66, 0.0);
	}
	if (data->player_init == 'W')
	{
		set_point(&player->dir, -1, 0);
		set_point(&player->dir_side, 0, -1);
		set_point(&player->plane, 0, -0.66);
	}
	if (data->player_init == 'E')
	{
		set_point(&player->dir, 1, 0);
		set_point(&player->dir_side, 0, 1);
		set_point(&player->plane, 0, 0.66);
	}
}

void	load_player(t_game *data, int x, int y)
{
	t_player	*player;

	player = (t_player *)ft_calloc(sizeof(t_player), 1);
	has_been_created(data, player);
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	load_dir_and_plane(data, player);
	data->player = player;
}
