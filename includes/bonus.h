/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:12:44 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/27 18:55:07 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H
# include "run_game.h"
# define POINTS 100
# define LIVES 3
# define TIME 30

t_point	pos_in_minimap(t_game *data, t_point src);
void	draw_triangle(t_game *data, int size, int color);
void	draw_circle_map(t_game *data, t_point center, double radius, int color);
void	draw_minimap(t_game *data);
char	get_value_table(t_game *data, int x, int y);
void	draw_sprites(t_game *data);
void	draw_rectangle(t_game *data, t_point_int start, t_point_int end, \
int color);
void	draw_triangle(t_game *data, int size, int color);
int		transparency_color(int color, double div);
void	init_collect_sp(t_game *data);
void	init_life(t_game *data);
void	copy_img(t_game *data, t_point_int start, t_point_int end, int text);
void	draw_lives(t_game *data);
void	collect_sprite(t_game *data, int x, int y);
void	rest_life(t_game *data);
void	game_over(t_game *data);
void	show_end_level(t_game *data);

#endif