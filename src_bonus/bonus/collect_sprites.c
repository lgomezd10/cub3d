#include "../../includes/bonus.h"

void delete_sprite(t_game *data, int x, int y)
{
	t_sprite *sp;
	t_sprite *found;

	sp = data->sprites.begin;
	found = 0;
	while (sp && !found)
	{		
		if ((int)sp->pos.x == x && (int)sp->pos.y == y)
		{
			found = sp;
			if (sp->next)
				sp->next->pre = sp->pre;
			else
				data->sprites.end = sp->pre;
			if (sp->pre)
				sp->pre->next = sp->next;
			else
				data->sprites.begin = sp->next;
			data->sprites.size--;

		}
		sp = sp->next;
	}
	if (found)
		free(found);
	else
		handle_error(data, "Not found sprite");
}

void load_next_level(t_game *data)
{
	char **maps;
	t_point_int dimensions;

	maps = data->bonus.maps;
	data->bonus.end = 1;
	if (data->bonus.levels > data->bonus.level)
	{
		data->bonus.level++;
		set_point_int(&dimensions, data->width, data->height);
		check_file(data, maps[data->bonus.level]);
		free_level(data);
		load_file(data, data->bonus.maps[data->bonus.level]);
		printf("se carga el archivo\n");
		check_wall_closed(data);
		printf("se comprueban las paredes\n");		
		data->width = dimensions.x;
		data->height = dimensions.y;
		data->bonus.end = 0;
		init_texture(data);
		init_minimap(data);
		init_game_bonus(data);       
	}
	else
		game_over(data);
}

void collect_sprite(t_game *data, int x, int y)
{
	t_point_int start;
	t_point_int end;
	data->table.table[y][x] = '0';
	delete_sprite(data, x, y);
	data->bonus.points += data->bonus.add_points;
	if (!data->sprites.size)
	{
		data->bonus.end = 1;
		set_point_int(&start, 0, 0);
		set_point_int(&end, data->width, data->height);
		draw_rectangle(data, start, end, color_int(0, 0, 0));
		printf("levels: %d level: %d\n", data->bonus.levels, data->bonus.level);
		if (data->bonus.levels > data->bonus.level)
			copy_img(data, start, end, NextLevel);
		else
			copy_img(data, start, end, GameOver);
	}
}

void init_collect_sp(t_game *data)
{
	t_bonus *bonus;

	bonus = &data->bonus;
	bonus->points = 0;
	bonus->lives = 1;
	bonus->add_points = POINTS / data->sprites.size;
}