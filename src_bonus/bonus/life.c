#include "../../includes/bonus.h"

void draw_life_bar(t_game *data)
{
	t_cont_img *img;
	t_point_int start;
	t_point_int end;
	t_life life;

	life = data->life;
	img = &data->window.img;
	start.x = 10;
	end.x = life.len_bar + 20;
	start.y = 10;
	end.y = start.y + 20;
	draw_rectangle(data, start, end, color_int(58, 199, 128));
	start.x += 10;
	end.x -= 10;
	start.y += 10;
	start.y -= 10;
	draw_rectangle(data, start, end, color_int(255, 215, 0));	
}

/*
void game_over(t_game *data)
{
	t_cont_img *img;
	t_cont_img *copy;
	int x;
	int y;
	int color;

	y = 0;
	img = &data->window.img;
	while (y < copy->height)
	{
		x =  0;
		while (x < copy->width)
		{
			color = my_mlx_pixel_get(copy, x, y);
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;		
	}
	mlx_put_image_to_window(data->window.ptr, \
		data->window.win, &img->img, 0, 0);
	
}
*/

void rest_life(t_game *data)
{
	data->life.points--;
	if (!data->life.points)
	{
		data->life.lives--;
		/*
		if (!data->life.lives)
			game_over(data);
		*/
	}
}

void init_life(t_game *data)
{
	t_life *life;

	life = &data->life;
	life->points = POINTS;
	life->lives = LIVES;
	life->len_bar = (data->width / 3) - 10;
	life->unit_bar = life->len_bar / POINTS;
}