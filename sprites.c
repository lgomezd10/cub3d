/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:32:05 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/12 19:02:25 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

void	calculate_sprite_screem(t_file *data, t_rc_sprites *ray_c)
{
	double	inv_det;
	t_point	pos_sp;
	t_point	pos;
	t_gamer	*gamer;

	pos = data->gamer->pos;
	gamer = data->gamer;
	ray_c->pos_sp.x = ray_c->sprite->pos.x - pos.x;
	ray_c->pos_sp.y = ray_c->sprite->pos.y - pos.y;
	pos_sp = ray_c->pos_sp;
	inv_det = (gamer->plane.x * gamer->dir.y - gamer->dir.x * gamer->plane.y);
	inv_det = 1.0 / inv_det;
	ray_c->trans.x = (gamer->dir.y * pos_sp.x - gamer->dir.x * pos_sp.y);
	ray_c->trans.x *= inv_det;
	ray_c->trans.y = (-gamer->plane.y * pos_sp.x + gamer->plane.x * pos_sp.y);
	ray_c->trans.y *= inv_det;
	ray_c->sp_screen_x = (int)((data->width / 2) * (1 + ray_c->trans.x / ray_c->trans.y));
	ray_c->sp_screen_x = (int)((data->width / 2) * (1 + ray_c->trans.x / ray_c->trans.y));
	ray_c->v_mv_screen = (int)(data->opt.v_move / ray_c->trans.y);
	
}

void	calculate_init_end_draw(t_file *data, t_rc_sprites *ray_c)
{
	ray_c->sp_height = abs((int)(data->height / (ray_c->trans.y))) / data->opt.v_div;
	ray_c->draw_start.y = -ray_c->sp_height / 2 + data->height / 2 + ray_c->v_mv_screen;
	if (ray_c->draw_start.y < 0)
		ray_c->draw_start.y = 0;
	ray_c->draw_end.y = ray_c->sp_height / 2 + data->height / 2 + ray_c->v_mv_screen;
	if (ray_c->draw_end.y >= data->height)
		ray_c->draw_end.y = data->height - 1;

	ray_c->sp_width = abs((int)(data->height / (ray_c->trans.y))) / data->opt.u_div;
	ray_c->draw_start.x = -ray_c->sp_width / 2 + ray_c->sp_screen_x;
	if (ray_c->draw_start.x < 0)
		ray_c->draw_start.x = 0;
	ray_c->draw_end.x = ray_c->sp_width / 2 + ray_c->sp_screen_x;
	if (ray_c->draw_end.x >= data->width)
		ray_c->draw_end.x = data->width - 1;
}

void	draw_line_with_texture(t_file *data, t_rc_sprites *ray_c)
{
	int	stripe;
	int	row;
	t_point	text;
	t_cont_img 	*texture;
	int	color;

	texture = &data->text[Sprite];
	stripe = ray_c->draw_start.x;
	while (stripe < ray_c->draw_end.x)
	{
		text.x = (int)(256 * (stripe - (-ray_c->sp_width / 2 + ray_c->sp_screen_x)) *  texture->width / ray_c->sp_width) / 256;
		if (ray_c->trans.y > 0 && stripe > 0 && stripe < data->width && ray_c->trans.y < data->wallDist[stripe])
		{
			row = ray_c->draw_start.y;
			while (row < ray_c->draw_end.y)
			{
				int d = (row - ray_c->v_mv_screen) * 256 - data->height * 128 + ray_c->sp_height * 128;
				text.y = ((d * texture->height) / ray_c->sp_height) / 256;
				color = my_mlx_pixel_get(texture, text.x, text.y);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&data->window.img, stripe, row, color);
				row++;
			}
		}
		stripe++;
	}
}

void print_sprites(t_file *data)
{
	t_rc_sprites ray_c;
	t_sprite *sprite;
	
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