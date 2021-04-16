#include "../../includes/run_game.h"

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

char move_minimap(t_game *data)
{
	t_point_int p_table;
	t_minimap *map;

	map = &data->minimap;
	map->init_table.x = data->player->pos.x - 10;
	map->end_table.x = data->player->pos.x + 10;
	if (map->init_table.x < 0)
	{
		map->end_table.x = 20;
		map->init_table.x = 0;
	}
	if (map->end_table.x >= data->table.cols)
	{
		map->end_table.x = data->table.cols - 1;
		map->init_table.x = map->end_table.x - 20;
	}
	map->init_table.y = data->player->pos.y - 10;
	map->init_table.y = data->player->pos.y + 10;
	if (map->init_table.y < 0)
	{
		map->end_table.y = 20;
		map->init_table.y = 0;
	}
	if (map->end_table.y >= data->table.cols)
	{
		map->end_table.y = data->table.cols - 1;
		map->init_table.y = map->end_table.x - 20;
	}
}

char get_value_table(t_game *data, int x, int y)
{
	t_point_int p_table;
	t_minimap *map;
	char **table;

	map = &data->minimap;
	table = data->table.table;

	p_table.y = (y - map->init.y) / map->unit_height;
	p_table.x = (x - map->init.x) / map->unit_width;
	p_table.y += map->init_table.y;
	p_table.x += map->init_table.x;
	return (table[p_table.y][p_table.x]);
}

void print_minimap(t_game *data)
{
	t_point_int scream;
	t_point_int p_table;
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
			p_table.y = (scream.y - map->init.y) / map->unit_height;
			p_table.x = (scream.x - map->init.x) / map->unit_width;
			if (valid_point(data, p_table.x, p_table.y))
			{
				if (get_value_table(data, scream.x,  scream.y) == '1')
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
	map->unit_width = map->width / 20;
	map->unit_height = map->height / 20;
	map->init.x = (map->width * 2) - map->unit_width;
	map->init.y = 0;
	map->color_player = color_int(255, 0, 0);
	map->color_walls = color_int(0, 0, 25);
	map->color_space = color_int(255, 255, 255);
	map->color_sprites = color_int(0, 255, 0);
}