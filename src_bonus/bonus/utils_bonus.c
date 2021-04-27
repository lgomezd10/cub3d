/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:25:07 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/27 17:25:10 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

char	*load_img_bonus(t_game *data, int dir)
{
	char	*str;

	str = 0;
	if (dir == GameOver)
		str = "textures/gameover.xpm";
	if (dir == NextLevel)
		str = "textures/nextlevel.xpm";
	if (dir == Life)
		str = "textures/life.xpm";
	if (dir == Blood)
		str = "textures/blood.xpm";
	if (dir == Beer)
		str = "textures/beer.xpm";
	if (str)
		check_file(data, str);
	return (str);
}

void	copy_img(t_game *data, t_point_int start, t_point_int end, int text)
{
	t_cont_img	*img;
	t_cont_img	*copy;
	t_point_int	pos;
	t_point_int	pos_copy;
	int			color;

	img = &data->window.img;
	copy = &data->text[text];
	pos.y = start.y;
	while (pos.y < end.y)
	{
		pos.x = start.x;
		while (pos.x < end.x)
		{
			pos_copy.x = ((pos.x - start.x) * copy->width) / (end.x - start.x);
			pos_copy.y = ((pos.y - start.y) * copy->height) / (end.y - start.y);
			color = my_mlx_pixel_get(copy, pos_copy.x, pos_copy.y);
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(img, pos.x, pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_rectangle(t_game *data, t_point_int start, t_point_int end, \
int color)
{
	int	x;
	int	y;

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
