#include "../../includes/bonus.h"

void draw_lives(t_game *data)
{
	t_point_int start;
	t_point_int end;
	t_point_int margin;
	int size;
	int i;

	size = data->width / 24;
	margin.x = size / 6;
	margin.y = margin.x;
	i = 0;
	while (i < data->bonus.lives && i < 6)
	{
		set_point_int(&start, margin.x, margin.y);
		set_point_int(&end, margin.x + size, margin.y + size);
		if (data->bonus.game == 1)
			copy_img(data, start, end, Life);
		if (data->bonus.game == 2)
			copy_img(data, start, end, Beer);
		margin.x += size + margin.y;
		i++;
	}
}

void game_over(t_game *data)
{
	t_cont_img *img;
	t_point_int start;
	t_point_int end;

	if (data->bonus.end)
	{
		img = &data->window.img;
		set_point_int(&start, 0, 0);
		set_point_int(&end, img->width, img->height);
		draw_rectangle(data, start, end, color_int(0, 0, 0));
		copy_img(data, start, end, GameOver);
		mlx_put_image_to_window(data->window.ptr, \
			data->window.win, img->img.img, 0, 0);
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
			data->bonus.ending = 1;
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
	bonus->add_points = 5;
}