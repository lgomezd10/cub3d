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

void game_over(t_game *data)
{
	t_cont_img *img;
	t_point_int start;
	t_point_int end;
	
	data->bonus.end = 1;
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
	end.x = start.x + (bonus.unit_bar * bonus.points) ;
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

void init_game_bonus(t_game *data)
{
    data->bonus.game = 2;
    if (data->bonus.game == 1)
        init_life(data);
    if (data->bonus.game == 2)
        init_collect_sp(data);
}