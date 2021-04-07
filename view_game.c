#include "cub3d.h"

void add_line_map(t_file *data, int side)
{

	t_point dest;
	t_view *view;
	t_point pos;

	view = &data->view;
	pos = data->gamer->position;
	if (side)
	{
		dest.y = view->map.y - data->view.step.y;
		if (view->rayDir.y > 0)
			dest.y++;				
		double dist = fabs((pos.y - dest.y) / view->rayDir.y);
		dest.x = pos.x + (view->rayDir.x * dist);
		
	}
	else
	{
		dest.x = view->map.x - data->view.step.x;
		if (view->rayDir.x > 0)
			dest.x++;
		double dist = fabs((pos.x - dest.x) / view->rayDir.x);
		dest.y = pos.y + (view->rayDir.y * dist);
	}
	if (dest.x >= 0 && dest.y >= 0 && dest.x < data->width && dest.y < data->height)
	   print_line(data, pos, dest, color_int(0, 0, 255), &data->map);
}

void calculate_dist(t_file *data)
{
	t_view *view;
	t_point pos;

	view = &data->view;
	pos = data->gamer->position;
	view->deltaDist.x = sqrt(1 + (view->rayDir.y * view->rayDir.y) / (view->rayDir.x * view->rayDir.x));
	view->deltaDist.y = sqrt(1 + (view->rayDir.x * view->rayDir.x) / (view->rayDir.y * view->rayDir.y));
	if (view->rayDir.x < 0)
	{
		view->step.x = -1;
		view->sideDist.x = (pos.x - view->map.x) * view->deltaDist.x;
	}
	else
	{
		view->step.x = 1;
		view->sideDist.x = (view->map.x + 1.0 - pos.x) * view->deltaDist.x;
	}
	if (view->rayDir.y < 0)
	{
		view->step.y = -1;
		view->sideDist.y = (pos.y - view->map.y) * view->deltaDist.y;
	}
	else
	{
		view->step.y = 1;
		view->sideDist.y = (view->map.y + 1.0 - pos.y) * view->deltaDist.y;
	}
}

int find_hit(t_file *data)
{
	t_view *view;
	int hit;
	int side;

	view = &data->view;
	hit = 0;
	while (!hit)
	{
		if (view->sideDist.x < view->sideDist.y)
		{			
			view->sideDist.x += view->deltaDist.x;
			view->map.x += view->step.x;
			side = 0;
		}
		else
		{
			view->sideDist.y += view->deltaDist.y;
			view->map.y += view->step.y;
			side = 1;
		}
		if (!in_space_int(data, view->map.x, view->map.y))
			hit = 1;
	}
	return (side);
}

t_cont_img *select_text(t_file *data, int side)
{
	if (!side)
	{
		if (data->view.rayDir.x < 0)
			return (&data->text[North]);
		else
			return (&data->text[South]);		
	}
	else
	{
		if (data->view.rayDir.y < 0)
			return (&data->text[West]);
		else
			return (&data->text[East]);
	}
	
}

void load_view(t_file *data, int x)
{
	t_view *view;
	t_point dir;
	t_point pos;
	t_point *plane;
	int hit = 0;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int color;
	t_point begin;
	t_point end;
	double wallX;
	t_point text;
	double step;
	double textPos;
	int i;
	t_cont_img *texture;
	
	pos = data->gamer->position;
	dir = data->gamer->direction;
	view = &data->view;
	plane = &data->gamer->plane;

	view->cameraX = 2 * x / (double)data->width - 1;
	view->rayDir.x = dir.x + plane->x * view->cameraX;
	view->rayDir.y = dir.y + plane->y * view->cameraX;
	view->map.x = (int)pos.x;
	view->map.y = (int)pos.y;
	//view->deltaDist.x = fabs(1 / view->rayDir.x);
	//view->deltaDist.y = fabs(1 / view->rayDir.y);
	calculate_dist(data);
	side = find_hit(data);
	if (data->gamer->act_map)
		add_line_map(data, side);

	
	if (side == 0)
		data->wallDist[x] = (view->map.x - pos.x + (1 - view->step.x) / 2) / view->rayDir.x;
	else
		data->wallDist[x] = (view->map.y - pos.y + (1 - view->step.y) / 2) / view->rayDir.y;
	lineHeight = (int)(data->height / data->wallDist[x]);
	drawStart = (-lineHeight / 2) + (data->height / 2);
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + data->height / 2;
	if (drawEnd >= data->height)
		drawEnd = data->height - 1;

	texture = select_text(data, side);
	if (side == 0)
		wallX = pos.y + data->wallDist[x] * view->rayDir.y;
	else
		wallX = pos.x + data->wallDist[x] * view->rayDir.x;
	wallX -= floor(wallX);
	text.x = (int)(wallX * (double)texture->width);
	if (!side && view->rayDir.x > 0)
		text.x = texture->width - text.x - 1;
	if (side && view->rayDir.x < 0)
		text.x = texture->width - text.x - 1;
	step = 1.0 * texture->height / lineHeight;
	textPos = (drawStart - data->height / 2 + lineHeight / 2) * step;
	i = drawStart;
	while (i < drawEnd)
	{
		text.y = (int)textPos & (texture->height - 1);
		textPos += step;
		color = my_mlx_pixel_get(texture, text.x, text.y);
		my_mlx_pixel_put(&data->window.img, x, i, color);
		i++;
	}

	/* VERSION COLORES
	if (side)
		color = color_int(0, 255, 0);
	else
		color = color_int(255, 0, 0);
	//printf("altura: %d start: %d, end %d\n", data->height, drawStart, drawEnd);
	
	print_line_real(data, x, drawStart, drawEnd, color, &data->window.img);
	*/
}

int view_game(t_file *data)
{
	int x;    
	x = 0;
	
	//while (x < 50)
	while (x < data->width)
	{
		load_view(data, x);
		x++;
	}
	

	return (0);
}