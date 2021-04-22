/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:47:22 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 12:19:46 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/run_game.h"

void	save_as_char(unsigned char *str, int nbr)
{
	str[0] = (unsigned char)(nbr);
	str[1] = (unsigned char)(nbr >> 8);
	str[2] = (unsigned char)(nbr >> 16);
	str[3] = (unsigned char)(nbr >> 24);
}

void	write_header(t_game *data, int fd, int file_size)
{
	unsigned char	header[54];

	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	save_as_char(&header[2], file_size);
	header[10] = (unsigned char) 54;
	header[14] = (unsigned char) 40;
	save_as_char(&header[18], data->width);
	save_as_char(&header[22], data->height);
	header[26] = (unsigned char) 1;
	header[28] = (unsigned char) 24;
	if (write(fd, &header, 54) < 0)
		handle_error(data, "Error to write screenshop.bmp");
}

void	write_image(t_game *data, int fd, int pad)
{
	int	x;
	int	y;
	int	color;

	y = data->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < data->width)
		{
			color = my_mlx_pixel_get(&data->window.img, x, y);
			if (write(fd, &color, 3) < 0)
				handle_error(data, "Error to write screenshop.bmp");
			x++;
		}
		if (write(fd, "\0\0\0", pad) < 0)
			handle_error(data, "Error to write screenshop.bmp");
		y--;
	}
}

void	save_bmp(t_game *data)
{
	int	fd;
	int	pad;
	int	file_size;

	pad = (4 - (data->width * 3) % 4) % 4;
	file_size = 54 + ((3 * data->width + pad) * data->height);
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd < 0)
		handle_error(data, "Can't open screenshop.bmp");
	write_header(data, fd, file_size);
	write_image(data, fd, pad);
	close(fd);
	ft_putendl_fd("screamshot.bmp has been created in this directory\n", 1);
	event_exit(data);
}

void	load_bmp(t_game *data)
{
	init_window(data);
	init_texture(data);
	data->window.img.img.img = mlx_new_image(data->window.ptr, \
	data->width, data->height);
	has_been_created(data, data->window.img.img.img);
	load_image(data);
}
