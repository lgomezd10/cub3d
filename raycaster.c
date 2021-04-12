/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:48:40 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/12 20:32:53 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	calculate_dist(t_file *data, t_view *view)
{
	t_point	pos;

	pos = data->gamer->pos;
	view->deltaDist.x = fabs(1 / view->rayDir.x);
	view->deltaDist.y = fabs(1 / view->rayDir.y);
	if (view->rayDir.x < 0)
	{
		view->step_ray.x = -1;
		view->sideDist.x = (pos.x - view->map.x) * view->deltaDist.x;
	}
	else
	{
		view->step_ray.x = 1;
		view->sideDist.x = (view->map.x + 1.0 - pos.x) * view->deltaDist.x;
	}
	if (view->rayDir.y < 0)
	{
		view->step_ray.y = -1;
		view->sideDist.y = (pos.y - view->map.y) * view->deltaDist.y;
	}
	else
	{
		view->step_ray.y = 1;
		view->sideDist.y = (view->map.y + 1.0 - pos.y) * view->deltaDist.y;
	}
}

void	calculate_line_to_draw(t_file *data, t_view *view, int x)
{
	t_point	pos;

	pos = data->gamer->pos;
	view->side = find_hit(data, view);
	if (view->side == 0)
	{
		data->wallDist[x] = (view->map.x - pos.x + (1 - view->step_ray.x) / 2);
		data->wallDist[x] /= view->rayDir.x;
	}
	else
	{
		data->wallDist[x] = (view->map.y - pos.y + (1 - view->step_ray.y) / 2);
		data->wallDist[x] /= view->rayDir.y;
	}
	view->lineHeight = (int)(data->height / data->wallDist[x]);
	view->drawStart = (-view->lineHeight / 2) + (data->height / 2);
	if (view->drawStart < 0)
		view->drawStart = 0;
	view->drawEnd = (view->lineHeight / 2) + (data->height / 2);
	if (view->drawEnd >= data->height)
		view->drawEnd = data->height - 1;
	if (view->side == 0)
		view->wallX = data->gamer->pos.y + data->wallDist[x] * view->rayDir.y;
	else
		view->wallX = data->gamer->pos.x + data->wallDist[x] * view->rayDir.x;
}

void	texture_to_image(t_file *data, t_view *view, int x)
{
	t_cont_img	*texture;
	int			i;

	texture = select_text(data, view);
	view->wallX -= floor(view->wallX);
	view->text.x = (int)(view->wallX * (double)texture->width);
	if (!view->side && view->rayDir.x > 0)
		view->text.x = texture->width - view->text.x - 1;
	if (view->side && view->rayDir.y < 0)
		view->text.x = texture->width - view->text.x - 1;
	view->step = 1.0 * texture->height / view->lineHeight;
	view->textPos = (view->drawStart - data->height / 2 + view->lineHeight / 2);
	view->textPos *= view->step;
	i = view->drawStart;
	while (i < view->drawEnd)
	{
		view->text.y = (int)view->textPos & (texture->height - 1);
		view->textPos += view->step;
		view->color = my_mlx_pixel_get(texture, view->text.x, view->text.y);
		if (view->side)
			view->color = (view->color >> 1) & 8355711;
		my_mlx_pixel_put(&data->window.img, x, i, view->color);
		i++;
	}
}

void	load_view(t_file *data, t_view *view, int x)
{	
	t_point	dir;
	t_point	pos;
	t_point	*plane;
	int		i;

	pos = data->gamer->pos;
	dir = data->gamer->dir;
	plane = &data->gamer->plane;
	view->cameraX = 2 * x / (double)data->width - 1;
	view->rayDir.x = dir.x + plane->x * view->cameraX;
	view->rayDir.y = dir.y + plane->y * view->cameraX;
	view->map.x = (int)pos.x;
	view->map.y = (int)pos.y;
	calculate_dist(data, view);
	calculate_line_to_draw(data, view, x);
	texture_to_image(data, view, x);
}

int	raycaster(t_file *data)
{
	int		x;
	t_view	view;

	x = 0;
	ft_bzero(&view, sizeof(t_view));
	while (x < data->width)
	{
		load_view(data, &view, x);
		x++;
	}
	print_sprites(data);
	return (0);
}
