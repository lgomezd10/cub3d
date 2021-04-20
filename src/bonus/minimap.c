#include "../../includes/bonus.h"

void	move_minimap(t_game *data)
{
	t_minimap	*map;

	map = &data->minimap;
	map->init_table.x = data->player->pos.x - map->size_map / 2;
	map->end_table.x = data->player->pos.x + map->size_map / 2;
	if (map->init_table.x < 0)
	{
		map->end_table.x = map->size_map - 1;
		map->init_table.x = 0;
	}
	if (map->end_table.x >= data->table.cols)
	{
		map->end_table.x = data->table.cols - 1;
		map->init_table.x = map->end_table.x - 1 - map->size_map;
	}
	map->init_table.y = data->player->pos.y - map->size_map / 2;
	map->end_table.y = data->player->pos.y + map->size_map / 2;
	if (map->init_table.y < 0)
	{
		map->end_table.y = map->size_map - 1;
		map->init_table.y = 0;
	}
	if (map->end_table.y >= data->table.cols)
	{
		map->end_table.y = data->table.cols - 1;
		map->init_table.y = map->end_table.y - 1 - map->size_map;
	}
}

char	get_value_table(t_game *data, int x, int y)
{
	t_point_int	p_table;
	t_minimap	*map;
	char		**table;

	map = &data->minimap;
	table = data->table.table;

	p_table.y = (y - map->init.y) / map->unit_height;
	p_table.x = (x - map->init.x) / map->unit_width;
	if (map->size_map)
	{
		p_table.y += map->init_table.y;
		p_table.x += map->init_table.x;
	}
	if (!valid_point(data, p_table.x, p_table.y))
	{
		printf("Se ha intentado acceder a x: %d y: %d\n", p_table.x, p_table.y);
		printf("Desde las coordenadas pasadas x: %d, y: %d\n", x, y);
		printf("con el init en pantalla x: %d, y: %d\n", map->init.x, map->init.y);
		printf("Y el inicio en tabla x: %d, y: %d\n", map->init_table.x, map->init_table.y);
		printf("Con la posicion del jugador x: %f, y: %f\n", data->player->pos.x, data->player->pos.y);
		printf("hay %d cols y % d rows\n", data->table.cols, data->table.rows);
		ft_errors("Error en minimap");
	}
	return (table[p_table.y][p_table.x]);
}

void	draw_minimap(t_game *data)
{
	t_point_int	scream;
	t_cont_img	*img;
	t_minimap	*map;

	img = &data->window.img;
	map = &data->minimap;
	scream.y = map->init.y;
	while (scream.y < map->height)
	{
		scream.x = map->init.x;
		while (scream.x < data->width - map->unit_width)
		{
			if (get_value_table(data, scream.x,  scream.y) == '1')
				my_mlx_pixel_put(img, scream.x, scream.y, map->color_walls);
			else
				my_mlx_pixel_put(img, scream.x, scream.y, map->color_space);			
			scream.x++;
		}
		scream.y++;
	}
	draw_sprites(data);
	draw_circle_map(data, data->player->pos, 4, map->color_player);
	draw_triangle(data, 8, map->color_player);
}

void init_minimap(t_game *data)
{
	t_minimap	*map;

	map = &data->minimap;
	map->width = data->width / 3;
	map->height = data->height / 3;
	map->size_map = 20;
	if (data->table.cols <= map->size_map || data->table.rows <= map->size_map)
		map->size_map = 0;
	if (map->size_map)
	{
		map->unit_width = map->width / map->size_map;
		map->unit_height = map->height / map->size_map;
	}
	else
	{
		map->unit_width = map->width / data->table.cols;
		map->unit_height = map->height / data->table.rows;
	}
	map->init.x = (map->width * 2) - map->unit_width;
	map->init.y = 0;
	map->color_player = color_int(255, 0, 0);
	map->color_walls = color_int(0, 0, 25);
	map->color_space = color_int(255, 255, 255);
	map->color_sprites = color_int(0, 255, 0);
}