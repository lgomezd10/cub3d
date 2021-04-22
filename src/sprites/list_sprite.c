/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:42:30 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/20 18:21:49 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_sprite	*add_new_sp_back(t_game *data, t_list_sp *list, int x, int y)
{
	t_sprite	*new;

	new = (t_sprite *)ft_calloc(sizeof(t_sprite), 1);
	has_been_created(data, new);
	new->pos.x = x + 0.5;
	new->pos.y = y + 0.5;
	if (!list->begin)
	{
		list->begin = new;
		list->end = new;
		list->size = 1;
		return (new);
	}
	list->end->next = new;
	new->pre = list->end;
	list->end = new;
	list->size++;
	return (new);
}

void	load_dist_sp(t_game *data)
{
	t_point		pos;
	t_point		pos_sp;
	t_sprite	*sprite;

	pos = data->player->pos;
	sprite = data->sprites.begin;
	while (sprite)
	{
		pos_sp = sprite->pos;
		sprite->dist = (pos.x - pos_sp.x) * (pos.x - pos_sp.x);
		sprite->dist += (pos.y - pos_sp.y) * (pos.y - pos_sp.y);
		sprite = sprite->next;
	}
}

void	move_to_prev(t_list_sp *list, t_sprite *to_move, t_sprite *next)
{
	if (to_move != next)
	{
		if (to_move == list->begin)
		{
			list->begin = to_move->next;
			list->begin->pre = 0;
		}
		else
		{
			if (to_move == list->end)
				list->end = to_move->pre;
			to_move->pre->next = to_move->next;
			if (to_move->next)
				to_move->next->pre = to_move->pre;
		}
		if (next == list->begin)
			list->begin = to_move;
		if (next->pre)
			next->pre->next = to_move;
		to_move->pre = next->pre;
		next->pre = to_move;
		to_move->next = next;
	}
}

t_sprite	*find_highest(t_sprite *list)
{
	t_sprite	*highest;

	highest = list;
	while (list)
	{
		if (list->dist > highest->dist)
			highest = list;
		list = list->next;
	}
	return (highest);
}

void	short_sprites(t_game *data)
{
	t_list_sp	*list;
	t_sprite	*highest;
	t_sprite	*act;

	load_dist_sp(data);
	list = &data->sprites;
	act = list->begin;
	while (act && act->next)
	{
		highest = find_highest(act);
		if (highest != act)
			move_to_prev(list, highest, act);
		else
			act = act->next;
	}
}
