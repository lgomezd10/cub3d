/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:16:05 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/22 15:57:00 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/run_game.h"

void	load_window(t_game *data)
{
	t_point_int	size;
	t_window	*win;

	win = &data->window;
	set_point_int(&win->img.init, 0, 0);
	data->window.ptr = mlx_init();
	mlx_get_screen_size(win->ptr, &size.x, &size.y);
	if (data->width > size.x)
		data->width = size.x;
	if (data->height > size.y)
		data->height = size.y - 23;
	if (data->width < 500)
		data->width = 500;
	if (data->height < 300)
		data->height = 300;
	data->wallDist = ft_calloc(sizeof(double), data->width);
	has_been_created(data, data->wallDist);
	win->img.width = data->width;
	win->img.height = data->height;
	win->img.unitHeight = win->img.height / data->table.rows;
	win->img.unitWidth = win->img.width / data->table.cols;
	if (!data->to_save)
		win->win = mlx_new_window(win->ptr, data->width, data->height, "CUB3D");
}

int	init_window(t_game *data)
{
	if (data->table.cols * data->table.rows > 900)
	{
		data->opt.mov_speed = 0.11;
		data->opt.rot_speed = 0.11;
	}
	else
	{
		data->opt.mov_speed = 0.06;
		data->opt.rot_speed = 0.03;
	}	
	data->opt.u_div = 1;
	data->opt.v_div = 1;
	data->opt.v_move = 0.0;
	load_window(data);
	init_minimap(data);
	init_life(data);
	return (0);
}

int	load_img(t_game *data, t_cont_img *img, int dir)
{
	char	*str;
	int		fd;

	str = 0;
	if (dir == North)
		str = data->t_NO;
	if (dir == South)
		str = data->t_SO;
	if (dir == East)
		str = data->t_EA;
	if (dir == West)
		str = data->t_WE;
	if (dir == Sprite)
		str = data->sprite;
	if (dir == GameOver)
	{
		
		str = "textures/gameover.xpm";
		fd = open(str, O_RDONLY);
		if (fd < 0)
			handle_error(data, "No se ha podido abrir el archivo");
		else
			close(fd);
	}
	if (dir == Life)
	{
		
		str = "textures/life.xpm";
		fd = open(str, O_RDONLY);
		if (fd < 0)
			handle_error(data, "No se ha podido abrir el archivo");
		else
			close(fd);
	}
	if (dir == Blood)
	{
		
		str = "textures/blood.xpm";
		fd = open(str, O_RDONLY);
		if (fd < 0)
			handle_error(data, "No se ha podido abrir el archivo");
		else
			close(fd);
	}
	img->img.img = mlx_xpm_file_to_image(data->window.ptr, \
	str, &img->width, &img->height);
	img->img.addr = mlx_get_data_addr(img->img.img, \
	&img->img.bpp, &img->img.line_length, &img->img.endian);
	return (0);
}

int	init_texture(t_game *data)
{
	t_cont_img	*text;

	text = (t_cont_img *)ft_calloc(sizeof(t_cont_img), Size);
	has_been_created(data, text);
	load_img(data, &text[North], North);
	load_img(data, &text[South], South);
	load_img(data, &text[East], East);
	load_img(data, &text[West], West);
	load_img(data, &text[Sprite], Sprite);
	load_img(data, &text[Life], Life);
	load_img(data, &text[GameOver], GameOver);
	load_img(data, &text[Blood], Blood);
	data->text = text;
	return (0);
}
