#include "../../includes/bonus.h"




void sprite_found(t_game *data, int x, int y)
{
    if (data->bonus.game == 1)
        rest_life(data);
    if (data->bonus.game == 2)
        collect_sprite(data, x, y);
}

void draw_life_bar(t_game *data)
{
	t_point_int start;
	t_point_int end;
	t_bonus bonus;

	bonus = data->bonus;
	start.x = data->width / 4;
	end.x = start.x + bonus.len_bar + 20;
	start.y = 10;
	end.y = start.y + 50;
	draw_rectangle(data, start, end, color_int(0, 0, 0));
	start.x += 10;
	end.x = start.x + bonus.len_bar;;
	start.y += 10;
	end.y -= 10;
	draw_rectangle(data, start, end, color_int(169, 169, 169));
	end.x = start.x + (int)(bonus.unit_bar * (double)bonus.points);
	draw_rectangle(data, start, end, color_int(255, 215, 0));
	draw_lives(data);
	set_point_int(&start, 0, 0);
	set_point_int(&end, data->width, data->height);
	if (bonus.blood)
	{
			copy_img(data, start, end, Blood);
			data->bonus.blood--;
	}
}

void check_next_level(t_game *data)
{
	static int temp = 0;
	t_bonus *bonus;

	bonus = &data->bonus;
	if (bonus->ending)
	{
		if (!temp)
			temp = 10;
		else
		{
			temp--;
			if (!temp)
			{
				bonus->ending = 0;
				bonus->end = 1;
			}
		}
	}
	if (bonus->end)
	{
		if (bonus->game == 1)
			game_over(data);
		if (bonus->game == 2)
			show_end_level(data);
	}
}

void init_game_bonus(t_game *data)
{
	t_bonus *bonus;

	bonus = &data->bonus;
	if (data->bonus.levels > 1)
    	data->bonus.game = 2;
	else
		data->bonus.game = 1;	
	bonus->len_bar = (data->width / 4) - 20;
	bonus->unit_bar = (double)bonus->len_bar / (double)POINTS;	
    if (data->bonus.game == 1)
        init_life(data);
    if (data->bonus.game == 2)
        init_collect_sp(data);
}