#include "../../includes/bonus.h"

void draw_lives(t_game *data)
{
	t_point_int start;
	t_point_int end;
	int size;
	int marginx;
	int marginy;
	int i;

	size = data->width / 24;
	marginx = size / 6;
	marginy = marginx;
	i = 0;
	while (i < data->bonus.lives && i < 6)
	{
		set_point_int(&start, marginx, marginy);
		set_point_int(&end, marginx + size, marginy + size);
		copy_img(data, start, end, Life);
		marginx += size + marginy;
		i++;
	}
}

void print_lives(t_game *data)
{
	char *lives;
	int x;
	int y;

	x = 20;
	y = 30;
	lives = ft_itoa(data->bonus.lives);
	mlx_string_put(data->window.ptr, data->window.win, x, y, color_int(255, 0, 0), lives);
	free(lives);
}



void rest_life(t_game *data)
{
	data->bonus.blood = TIME;
	data->bonus.points -= data->bonus.add_points;
	if (!data->bonus.points)
	{		
		data->bonus.lives--;
		if (!data->bonus.lives)
			game_over(data);
		else
			data->bonus.points = POINTS;
	}
}

void init_life(t_game *data)
{
	t_bonus *bonus;

	bonus = &data->bonus;
	bonus->points = POINTS;
	bonus->lives = LIVES;
	bonus->len_bar = (data->width / 4) - 10;
	bonus->unit_bar = bonus->len_bar / POINTS;
	bonus->add_points = 5;
}