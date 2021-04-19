#include "../../includes/run_game.h"

void draw_triangle(t_game *data, int size, int color)
{
	t_player *player;
	t_point pos;
	t_point_int draw;
	t_point_int add;
	int sizey;

	player = data->player;
	pos.x = data->minimap.init.x + ((player->pos.x - data->minimap.init_table.x) * data->minimap.unit_width);
	pos.y = data->minimap.init.y + ((player->pos.y - data->minimap.init_table.y) * data->minimap.unit_height);
	add.x = 0;
	sizey = size;
	while (sizey > 0)
	{
		add.y = -sizey;
		while (add.y <= sizey)
		{
			draw.x = pos.x + (add.y * player->dir_side.x);
			draw.y = pos.y + (add.y * player->dir_side.y);
			my_mlx_pixel_put(&data->window.img, draw.x, draw.y, color);
			add.y++;
		}
		sizey--;
		add.x++;
		pos.x = pos.x + (player->dir.x);
		pos.y = pos.y + (player->dir.y);		
	}
}

void draw_circle_map(t_game *data, t_point center, double radius, int color)
{
	int i;
	int j;
	int to_y;
	int to_x;
	t_point point;

	center.x = data->minimap.init.x + ((center.x -data->minimap.init_table.x) * data->minimap.unit_width);
	center.y = data->minimap.init.y + ((center.y - data->minimap.init_table.y) * data->minimap.unit_height);
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
				my_mlx_pixel_put(&data->window.img, j, i, color);
			j++;
		}
		i++;
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
