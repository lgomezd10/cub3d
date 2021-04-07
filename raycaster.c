#include "raycaster.h"

void add_line_map(t_file *data,  t_view *view)
{

	t_point dest;
	t_point pos;
	double dist;
	
	pos = data->gamer->pos;
	if (view->side)
	{
		dest.y = view->map.y - view->step_ray.y;
		if (view->rayDir.y > 0)
			dest.y++;				
		dist = fabs((pos.y - dest.y) / view->rayDir.y);
		dest.x = pos.x + (view->rayDir.x * dist);
		
	}
	else
	{
		dest.x = view->map.x - view->step_ray.x;
		if (view->rayDir.x > 0)
			dest.x++;
		dist = fabs((pos.x - dest.x) / view->rayDir.x);
		dest.y = pos.y + (view->rayDir.y * dist);
	}
	if (dest.x >= 0 && dest.y >= 0 && dest.x < data->width && dest.y < data->height)
	   print_line(data, pos, dest, color_int(0, 0, 255), &data->map);
}

void calculate_dist(t_file *data, t_view *view)
{
	t_point pos;

	pos = data->gamer->pos;
	view->deltaDist.x = sqrt(1 + (view->rayDir.y * view->rayDir.y) / (view->rayDir.x * view->rayDir.x));
	view->deltaDist.y = sqrt(1 + (view->rayDir.x * view->rayDir.x) / (view->rayDir.y * view->rayDir.y));
	if (view->rayDir.x < 0)
	{
		view->step_ray.x = -1;
		view->sideDist.x = (pos.x - view->map.x) * view->deltaDist.x;
	}
	else
	{
		view->step_ray.x = 1;
		view->sideDist.x = (view->map.x + 1.0 - pos.x) * view->deltaDist.x;
	}
	if (view->rayDir.y < 0)
	{
		view->step_ray.y = -1;
		view->sideDist.y = (pos.y - view->map.y) * view->deltaDist.y;
	}
	else
	{
		view->step_ray.y = 1;
		view->sideDist.y = (view->map.y + 1.0 - pos.y) * view->deltaDist.y;
	}
}

int find_hit(t_file *data, t_view *view)
{	
	int hit;

	hit = 0;
	while (!hit)
	{
		if (view->sideDist.x < view->sideDist.y)
		{			
			view->sideDist.x += view->deltaDist.x;
			view->map.x += view->step_ray.x;
			view->side = 0;
		}
		else
		{
			view->sideDist.y += view->deltaDist.y;
			view->map.y += view->step_ray.y;
			view->side = 1;
		}
		if (!in_space_int(data, view->map.x, view->map.y))
			hit = 1;
	}
	return (view->side);
}

t_cont_img *select_text(t_file *data, t_view *view)
{
	if (!view->side)
	{
		if (view->rayDir.x < 0)
			return (&data->text[North]);
		else
			return (&data->text[South]);		
	}
	else
	{
		if (view->rayDir.y < 0)
			return (&data->text[West]);
		else
			return (&data->text[East]);
	}
	
}

void calculate_line_to_draw(t_file *data, t_view *view, int x)
{
	t_point pos;

	pos = data->gamer->pos;
	view->side = find_hit(data, view);
	if (data->gamer->act_map)
		add_line_map(data, view);	
	if (view->side == 0)
		data->wallDist[x] = (view->map.x - pos.x + (1 - view->step_ray.x) / 2) / view->rayDir.x;
	else
		data->wallDist[x] = (view->map.y - pos.y + (1 - view->step_ray.y) / 2) / view->rayDir.y;
	view->lineHeight = (int)(data->height / data->wallDist[x]);
	view->drawStart = (-view->lineHeight / 2) + (data->height / 2);
	if (view->drawStart < 0)
		view->drawStart = 0;
	view->drawEnd = view->lineHeight / 2 + data->height / 2;
	if (view->drawEnd >= data->height)
		view->drawEnd = data->height - 1;
	
}

void texture_to_image(t_file *data, t_view *view, int x)
{
	t_cont_img *texture;
	int i;

	texture = select_text(data, view);
	if (view->side == 0)
		view->wallX = data->gamer->pos.y + data->wallDist[x] * view->rayDir.y;
	else
		view->wallX = data->gamer->pos.x + data->wallDist[x] * view->rayDir.x;
	view->wallX -= floor(view->wallX);
	view->text.x = (int)(view->wallX * (double)texture->width);
	if (!view->side && view->rayDir.x > 0)
		view->text.x = texture->width - view->text.x - 1;
	if (view->side && view->rayDir.x < 0)
		view->text.x = texture->width - view->text.x - 1;
	view->step = 1.0 * texture->height / view->lineHeight;
	view->textPos = (view->drawStart - data->height / 2 + view->lineHeight / 2) * view->step;
	i = view->drawStart;
	while (i < view->drawEnd)
	{
		view->text.y = (int)view->textPos & (texture->height - 1);
		view->textPos += view->step;
		view->color = my_mlx_pixel_get(texture, view->text.x, view->text.y);
		my_mlx_pixel_put(&data->window.img, x, i, view->color);
		i++;
	}
}

void load_view(t_file *data, t_view *view, int x)
{	
	t_point dir;
	t_point pos;
	t_point *plane;
	int i;
	
	pos = data->gamer->pos;
	dir = data->gamer->dir;
	plane = &data->gamer->plane;
	view->cameraX = 2 * x / (double)data->width - 1;
	view->rayDir.x = dir.x + plane->x * view->cameraX;
	view->rayDir.y = dir.y + plane->y * view->cameraX;
	view->map.x = (int)pos.x;
	view->map.y = (int)pos.y;
	//view->deltaDist.x = fabs(1 / view->rayDir.x);
	//view->deltaDist.y = fabs(1 / view->rayDir.y);
	calculate_dist(data, view);
	calculate_line_to_draw(data, view, x);
	texture_to_image(data, view, x);

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
	t_view view;
	
	//while (x < 50)
	ft_bzero(&view, sizeof(t_view));
	while (x < data->width)
	{
		load_view(data, &view, x);
		x++;
	}
	return (0);
}