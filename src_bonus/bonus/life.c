#include "../../includes/bonus.h"

void copy_img(t_game *data, t_point_int start, t_point_int end, int text)
{
	t_cont_img *img;
	t_cont_img *copy;
	t_point_int pos;
	t_point_int pos_copy;
	int color;
	img = &data->window.img;
	copy = &data->text[text];
	pos.y = start.y;
	while (pos.y < end.y)
	{
		pos.x = start.x;
		while (pos.x < end.x)
		{
			pos_copy.x = ((pos.x - start.x) * copy->width) / (end.x - start.x);
			pos_copy.y = ((pos.y - start.y) * copy->height) / (end.y - start.y);
			color = my_mlx_pixel_get(copy, pos_copy.x, pos_copy.y);
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(img, pos.x, pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}

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
	while (i < data->life.lives && i < 6)
	{
		set_point_int(&start, marginx, marginy);
		set_point_int(&end, marginx + size, marginy + size);
		copy_img(data, start, end, Life);
		marginx += size + marginy;
		i++;
	}
}

void draw_life_bar(t_game *data)
{
	t_point_int start;
	t_point_int end;
	t_life life;

	life = data->life;
	start.x = data->width / 4;
	end.x = start.x + life.len_bar + 20;
	start.y = 10;
	end.y = start.y + 50;
	draw_rectangle(data, start, end, color_int(0, 0, 0));
	start.x += 10;
	end.x = start.x + life.len_bar;;
	start.y += 10;
	end.y -= 10;
	draw_rectangle(data, start, end, color_int(169, 169, 169));
	end.x = start.x + (life.unit_bar * life.points) ;
	draw_rectangle(data, start, end, color_int(255, 215, 0));
	draw_lives(data);
	set_point_int(&start, 0, 0);
	set_point_int(&end, data->width, data->height);
	if (life.blood)
	{
			copy_img(data, start, end, Blood);
			data->life.blood--;
	}
}

void print_lives(t_game *data)
{
	char *lives;
	int x;
	int y;

	x = 20;
	y = 30;
	lives = ft_itoa(data->life.lives);
	mlx_string_put(data->window.ptr, data->window.win, x, y, color_int(255, 0, 0), lives);
	free(lives);
}



void game_over(t_game *data)
{
	t_cont_img *img;
	t_point_int start;
	t_point_int end;
	
	data->life.dead = 1;
	if (data->life.dead)
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

void rest_life(t_game *data)
{
	data->life.blood = TIME;
	data->life.points -= 5;
	if (!data->life.points)
	{		
		data->life.lives--;
		if (!data->life.lives)
			game_over(data);
		else
			data->life.points = POINTS;
	}
}

void init_life(t_game *data)
{
	t_life *life;

	life = &data->life;
	life->points = POINTS;
	life->lives = LIVES;
	life->len_bar = (data->width / 4) - 10;
	life->unit_bar = life->len_bar / POINTS;
}