/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:15:58 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/22 15:58:35 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	press_key(int keycode, t_game *data)
{
	t_player	*player;

	player = data->player;
	
	if (keycode == K_NEXT && data->bonus.game == 2 && data->bonus.end)
	{
		data->bonus.end = 0;
		load_next_level(data);
	}
	if (keycode == K_RIGHT)
		player->move_in_side = -1;
	if (keycode == K_LEFT)
		player->move_in_side = 1;
	if (keycode == K_UP)
		player->move_in_dir = -1;
	if (keycode == K_DOWN)
		player->move_in_dir = 1;
	if (keycode == K_TURN_L)
		player->rotate = -1;
	if (keycode == K_TURN_R)
		player->rotate = 1;
	if (keycode == K_MAP)
	{
		player->act_map = !player->act_map;
		data->has_moved = 1;
	}
	if (keycode == K_ESC)
		event_exit(data);
	return (0);
}

int	release_key(int keycode, t_game *data)
{
	t_player	*player;

	player = data->player;
	if (keycode == K_LEFT)
		player->move_in_side = 0;
	if (keycode == K_RIGHT)
		player->move_in_side = 0;
	if (keycode == K_UP)
		player->move_in_dir = 0;
	if (keycode == K_DOWN)
		player->move_in_dir = 0;
	if (keycode == K_TURN_L)
		player->rotate = 0;
	if (keycode == K_TURN_R)
		player->rotate = 0;
	return (0);
}

int	event_exit(t_game *data)
{
	data->closed = 1;
	printf("Game over!\n");
	free_components(data);
	exit(0);
	return (0);
}
