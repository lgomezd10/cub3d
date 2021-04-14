/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:32:05 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/14 18:49:14 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sprites.h"

void	calculate_sprite_screem(t_game *data, t_rc_sprites *ray_c)
{
	double	inv_det;
	t_point	pos_sp;
	t_point	pos;
	t_point	transf;
	t_player	*player;

	pos = data->player->pos;
	player = data->player;
	ray_c->pos_sp.x = ray_c->sprite->pos.x - pos.x;
	ray_c->pos_sp.y = ray_c->sprite->pos.y - pos.y;
	pos_sp = ray_c->pos_sp;
	inv_det = (player->plane.x * player->dir.y - player->dir.x * player->plane.y);
	inv_det = 1.0 / inv_det;
	ray_c->transf.x = (player->dir.y * pos_sp.x - player->dir.x * pos_sp.y);
	ray_c->transf.x *= inv_det;
	ray_c->transf.y = (-player->plane.y * pos_sp.x + player->plane.x * pos_sp.y);
	ray_c->transf.y *= inv_det;
	transf = ray_c->transf;
	ray_c->sp_screen_x = (int)((data->width / 2) * (1 + transf.x / transf.y));
	ray_c->sp_screen_x = (int)((data->width / 2) * (1 + transf.x / transf.y));
	ray_c->v_mv_screen = (int)(data->opt.v_move / transf.y);
}

void	calculate_init_end_draw(t_game *data, t_rc_sprites *ray_c)
{
	t_point	transf;
	int		sp_height;
	int		sp_width;
	int		v_mv_screen;

	transf = ray_c->transf;
	v_mv_screen = ray_c->v_mv_screen;
	ray_c->sp_height = abs((int)(data->height / (transf.y)));
	ray_c->sp_height /= data->opt.v_div;
	sp_height = ray_c->sp_height;
	ray_c->draw_start.y = -sp_height / 2 + data->height / 2 + v_mv_screen;
	if (ray_c->draw_start.y < 0)
		ray_c->draw_start.y = 0;
	ray_c->draw_end.y = sp_height / 2 + data->height / 2 + v_mv_screen;
	if (ray_c->draw_end.y >= data->height)
		ray_c->draw_end.y = data->height - 1;
	ray_c->sp_width = abs((int)(data->height / (transf.y))) / data->opt.u_div;
	sp_width = ray_c->sp_width;
	ray_c->draw_start.x = -sp_width / 2 + ray_c->sp_screen_x;
	if (ray_c->draw_start.x < 0)
		ray_c->draw_start.x = 0;
	ray_c->draw_end.x = sp_width / 2 + ray_c->sp_screen_x;
	if (ray_c->draw_end.x >= data->width)
		ray_c->draw_end.x = data->width - 1;
}

void	copy_texture_to_point(t_game *data, t_rc_sprites *ray_c, int stripe)
{
	t_point		p_text;
	t_cont_img	*text;
	int			row;
	int			color;
	int			d;

	text = &data->text[Sprite];
	p_text.x = (stripe - (-ray_c->sp_width / 2 + ray_c->sp_screen_x));
	p_text.x = (int)(256 * p_text.x * text->width / ray_c->sp_width) / 256;
	if (ray_c->transf.y > 0 && stripe > 0 && stripe < data->width
		&& ray_c->transf.y < data->wallDist[stripe])
	{
		row = ray_c->draw_start.y;
		while (row < ray_c->draw_end.y)
		{
			d = (row - ray_c->v_mv_screen) * 256 - data->height * 128;
			d += ray_c->sp_height * 128;
			p_text.y = ((d * text->height) / ray_c->sp_height) / 256;
			color = my_mlx_pixel_get(text, p_text.x, p_text.y);
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&data->window.img, stripe, row, color);
			row++;
		}
	}
}

void	draw_line_with_texture(t_game *data, t_rc_sprites *ray_c)
{
	int	stripe;

	stripe = ray_c->draw_start.x;
	while (stripe < ray_c->draw_end.x)
	{
		copy_texture_to_point(data, ray_c, stripe);
		stripe++;
	}
}

void	print_sprites(t_game *data)
{
	t_rc_sprites	ray_c;
	t_sprite		*sprite;

	sprite = data->sprites.begin;
	while (sprite)
	{
		ft_bzero(&ray_c, sizeof(ray_c));
		ray_c.sprite = sprite;
		calculate_sprite_screem(data, &ray_c);
		calculate_init_end_draw(data, &ray_c);
		draw_line_with_texture(data, &ray_c);
		sprite = sprite->next;
	}
}
