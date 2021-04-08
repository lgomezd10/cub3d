#include "cub3d.h"

void print_sprites(t_file *data)
{
	t_sprite *sprite;
	t_point pos_sp;
	t_point pos;
	double invDet;
	t_gamer *gamer;
	t_point trans;
	int sp_screenx;
	int vMoveScreen;
	int sp_height;
	int sp_width;
	t_point_int draw_start;
	t_point_int draw_end;
	t_point_int text;
	int sp;
	t_cont_img *texture;
	int color;

	texture = &data->text[Sprite];
	sprite = data->sprites.begin;
	pos = data->gamer->pos;
	gamer = data->gamer;
	while (sprite)
	{
		pos_sp.x = sprite->pos.x - pos.x;
		pos_sp.y = sprite->pos.y - pos.y;

		invDet = 1.0 / (gamer->plane.x * gamer->dir.y - gamer->dir.x * gamer->plane.y);

		trans.x = invDet * (gamer->dir.y * pos_sp.x - gamer->dir.x * pos_sp.y);
		trans.y = invDet * (-gamer->plane.y * pos_sp.x + gamer->plane.x * pos_sp.y);

		sp_screenx = (int)((data->width / 2) * (1 + trans.x / trans.y));

		vMoveScreen = (int)(data->opt.v_move / trans.y);

		sp_height = abs((int)(data->height / (trans.y))) / data->opt.v_div;
		draw_start.y = -sp_height / 2 + data->height / 2 + vMoveScreen;
		if (draw_start.y < 0)
			draw_start.y = 0;
		draw_end.y = sp_height / 2 + data->height / 2 + vMoveScreen;
		if (draw_end.y >= data->height)
			draw_end.y = data->height - 1;

		sp_width = abs((int)(data->height / (trans.y))) / data->opt.u_div;
		draw_start.x = -sp_width / 2 + sp_screenx;
		if (draw_start.x < 0)
			draw_start.x = 0;
		draw_end.x = sp_width / 2 + sp_screenx;
		if (draw_end.x >= data->width)
			draw_end.x = data->width - 1;

		sp = draw_start.x;
		while (sp < draw_end.x)
		{
			text.x = (int)(256 * (sp - (-sp_width / 2 + sp_screenx)) *  texture->width / sp_width) / 256;
			if (trans.y > 0 && sp > 0 && sp < data->width && trans.y < data->wallDist[sp])
			{
				int y = draw_start.y;
				while (y < draw_end.y)
				{
					int d = (y - vMoveScreen) * 256 - data->height * 128 + sp_height * 128;
					text.y = ((d * texture->height) / sp_height) / 256;
					color = my_mlx_pixel_get(texture, text.x, text.y);
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&data->window.img, sp, y, color);
					y++;
				}
			}
			sp++;
		}
		sprite = sprite->next;
	}
}