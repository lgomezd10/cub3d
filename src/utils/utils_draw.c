#include "../../includes/run_game.h"

void draw_circle(t_cont_img *img, t_point center, double radius, int color)
{
	int i;
	int j;
	int to_y;
	int to_x;
	t_point point;

	center.x *= img->unitWidth;
	center.y *= img->unitHeight;
	i = center.y - radius;
	to_y = i + (2 * radius);
	while (i <= to_y)
	{
		j = center.x - radius;
		to_x = j + (2 * radius);
		while (j <= to_x)
		{			
			point.x = j;
			point.y = i;
			if (is_in_radius(point, center, radius))
				my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

void print_line(t_point from, t_point to, int color, t_cont_img *img)
{
	double x;
	double y;
	int end;

	from.x *= img->unitWidth;
	from.y *= img->unitHeight;
	to.x *= img->unitWidth;
	to.y *= img->unitHeight;
	x = from.x;
	y = from.y;
	end = to.x;
	if (fabs(to.x - from.x) < fabs(to.y - from.y))
	{
		end = to.y;
		y = from.y;
		if (to.y < from.y)
		{
			end = from.y;
			y = to.y;
		}
		x = from.x;
		while (y < end && x < img->width && y < img->height)
		{
			x = ((y - from.y) / (to.y - from.y)) * (to.x - from.x) + from.x;
			my_mlx_pixel_put(img, x, y, color);
			y++;
		}
	}
	else
	{
		end = to.x;
		x = from.x;
		if (to.x < from.x)
		{
			end = from.x;
			x = to.x;
		}
		y = from.y;
		while (x < end && x < img->width && y < img->height)
		{
			y = ((x - from.x) / (to.x - from.x)) * (to.y - from.y) + from.y;
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
	}
}

void print_line_real(t_game *data, int x, int start, int end, int color, t_cont_img *img)
{
	
	if (end < start)
		ft_errors("start es mayor que end en print_line_real");
	if (start < 0 || start >= data->height)
		ft_errors("start esta fuera de los limites");
	if (end < 0 || end >= data->height)
		ft_errors("end esta fuera de los limites");
	
	while (start < end)
	{
		my_mlx_pixel_put(img, x, start, color);
		start++;
	}
}

void print_cel_floor(t_game *data, int ceiling, int floor, t_cont_img *img)
{
	int i;
	int j;

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



void print_map(t_game *data, t_cont_img *img)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{   
			//printf("prueba 2.1\n");
			y = i / img->unitHeight;
			x = j / img->unitWidth;
			if (data->table.table[y][x] == '1')
				my_mlx_pixel_put(img, j, i, color_int(0, 0, 25));
			if (data->table.table[y][x] == '0' || data->table.table[y][x] == '*')
				my_mlx_pixel_put(img, j, i, color_int(255, 255, 255));
			if (data->table.table[y][x] == '2')
				my_mlx_pixel_put(img, j, i, color_int(0, 255, 0));
			
			j++;
		}		
		i++;
	}
}

int color_int(int red, int green, int blue)
{
	return (red * 65536 + green * 256 + blue);
}

void my_mlx_pixel_put(t_cont_img *img, int x, int y, int color)
{
	char    *dst;
	t_image *data;

	data = &img->img;
	if (data->img && x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

unsigned int my_mlx_pixel_get(t_cont_img *img, int x, int y)
{
	char    *dst;
	t_image *data;

	data = &img->img;
	if (data->img && x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		return (*(unsigned int*)dst);
	}
	return(0);
}
