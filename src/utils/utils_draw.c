#include "../../includes/run_game.h"



void	print_cel_floor(t_game *data, int ceiling, int floor, t_cont_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height / 2)
	{
		j = 0;
		while (j < data->width)
		{
			my_mlx_pixel_put(img, j, i, ceiling);
			j++;
		}
		i++;
	}
	i = data->height / 2;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			my_mlx_pixel_put(img, j, i, floor);
			j++;
		}
		i++;
	}	
}

int	color_int(int red, int green, int blue)
{
	return (red * 65536 + green * 256 + blue);
}

void	my_mlx_pixel_put(t_cont_img *img, int x, int y, int color)
{
	char	*dst;
	t_image	*data;

	data = &img->img;
	if (data->img && x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

unsigned int	my_mlx_pixel_get(t_cont_img *img, int x, int y)
{
	char	*dst;
	t_image	*data;

	data = &img->img;
	if (data->img && x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		return (*(unsigned int*)dst);
	}
	return(0);
}
