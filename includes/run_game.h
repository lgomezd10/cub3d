/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:14:16 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/22 19:41:20 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_GAME_H
# define RUN_GAME_H
# include "cub3d.h"

void			short_sprites(t_game *data);
void			draw_minimap(t_game *data);
void			init_minimap(t_game *data);
int				init_texture(t_game *data);
void			print_cel_floor(t_game *data, int ceiling, int floor, \
t_cont_img *img);
int				raycaster(t_game *data);
int				press_key(int keycode, t_game *data);
int				release_key(int keycode, t_game *data);
void			my_mlx_pixel_put(t_cont_img *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_cont_img *img, int x, int y);
int				init_window(t_game *data);
void			print_sprites(t_game *data);
int				is_in_radius(t_point point, t_point center, double radius);
int				in_space(t_game *data, double x, double y);
int				in_space_int(t_game *data, int x, int y);
int				load_image(t_game *data);
int				move(t_game *data);
int				color_int(int red, int green, int blue);
void			save_bmp(t_game *data);
void			move_minimap(t_game *data);
void            draw_life_bar(t_game *data);
void            game_over(t_game *data);
void            init_game_bonus(t_game *data);
void            sprite_found(t_game *data, int x, int y);
#endif