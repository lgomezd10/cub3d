#include "includes/run_game.h"

void draw_circle_map(t_game *data, t_point center, double radius, int color)
{
	int i;
	int j;
	int to_y;
	int to_x;
	t_point point;

	center.x = data->minimap.init.x + (center.x * data->minimap.unit_width);
	center.y = data->minimap.init.y + (center.y * data->minimap.unit_height);
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

void draw_sprites(t_game *data)
{
	t_sprite *list;

	list = data->sprites.begin;
	while (list)
	{
		draw_circle_map(data, list->pos, 6, data->minimap.color_sprites);
		list = list->next;
	}	
}

void print_minimap(t_game *data)
{
	t_point_int scream;
	int x;
	int y;
	t_cont_img *img;
	t_minimap *map;

	img = &data->window.img;
	map = &data->minimap;
	scream.y = map->init.y;
	while (scream.y < map->height)
	{
		scream.x = map->init.x;
		while (scream.x < data->width - map->unit_width)
		{
			y = (scream.y - map->init.y) / map->unit_height;
			x = (scream.x - map->init.x) / map->unit_width;
			if (x >= 0 && x < data->table.cols && y >= 0 && y < data->table.rows)
			{
				if (data->table.table[y][x] == '1')
					my_mlx_pixel_put(img, scream.x, scream.y, map->color_walls);
				else
					my_mlx_pixel_put(img, scream.x, scream.y, map->color_space);
			}
			scream.x++;
		}
		scream.y++;
	}
	draw_sprites(data);
	draw_circle_map(data, data->player->pos, 4, map->color_player);
}

void init_minimap(t_game *data)
{
	t_minimap *map;

	map = &data->minimap;
	map->width = data->width / 3;
	map->height = data->height / 3;
	map->unit_width = map->width / data->table.cols;
	map->unit_height = map->height / data->table.rows;
	map->init.x = (map->width * 2) - map->unit_width;
	map->init.y = 0;
	map->color_player = color_int(255, 0, 0);
	map->color_walls = color_int(0, 0, 25);
	map->color_space = color_int(255, 255, 255);
	map->color_sprites = color_int(0, 255, 0);
}