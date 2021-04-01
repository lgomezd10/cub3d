#include "cub3d.h"

void load_view(t_file *data, int x)
{
	t_view *view;
	t_point dir;
	t_point pos;
	t_point *plane;
	int hit = 0;
	int side;
	t_point dest;
	char c;
	t_point dir1;
	double perpWallDist;

	//pos = data->gamer->position;
	//pos.x = data->gamer->position.x / data->gamer->unitWidth;
	//pos.y = data->gamer->position.y / data->gamer->unitHeight;
	pos.x = 9;
	pos.y = 6;
	dir = data->gamer->direction;
	view = &data->view;
	plane = &data->gamer->plane;

	view->cameraX = 2 * x / (double)data->width - 1;
	view->rayDir.x = dir.x + plane->x * view->cameraX;
	view->rayDir.y = dir.y + plane->y * view->cameraX;
	dir1.x = data->gamer->position.x + (view->rayDir.x * 30);
	dir1.y = data->gamer->position.y + (view->rayDir.y * 30);
	print_line(data, data->gamer->position, dir1, color_int(0,255,0), &data->window.img);
	view->map.x = (int)pos.x;
	view->map.y = (int)pos.y;
	//view->deltaDist.x = fabs(1 / view->rayDir.x);
	//view->deltaDist.y = fabs(1 / view->rayDir.y);
	view->deltaDist.x = sqrt(1 + (view->rayDir.y * view->rayDir.y) / (view->rayDir.x * view->rayDir.x));
	view->deltaDist.y = sqrt(1 + (view->rayDir.x * view->rayDir.x) / (view->rayDir.y * view->rayDir.y));
	printf("EMPEZANDO con POS: x: %f, y: %f deltaDist: x: %f y: %f\n", pos.x, pos.y, view->deltaDist.x, view->deltaDist.y);
	if (view->rayDir.x < 0)
	{
		view->step.x = -1;
		view->sideDist.x = (pos.x - view->map.x) * view->deltaDist.x;
		printf("asignado en x < 0 side.x %f\n", view->sideDist.x);
	}
	else
	{
		view->step.x = 1;
		view->sideDist.x = (view->map.x + 1.0 - pos.x) * view->deltaDist.x;
		printf("asignado en x > 0 side.x %f\n", view->sideDist.x);
	}
	if (view->rayDir.y < 0)
	{
		view->step.y = -1;
		view->sideDist.y = (pos.y - view->map.y) * view->deltaDist.y;
		printf("asignado en y < 0 side.y %f\n", view->sideDist.y);
	}
	else
	{
		view->step.y = 1;
		view->sideDist.y = (view->map.y + 1.0 - pos.y) * view->deltaDist.y;
		printf("asignado en y > 0 side.y %f\n", view->sideDist.y);
	}
	hit = 0;
	printf("EMPEZANDO EN x: %d, y: %d deltaDist: x: %f y: %f\n", view->map.x, view->map.y, view->sideDist.x, view->sideDist.y);
	while (!hit)
	{
		if (view->sideDist.x < view->sideDist.y)
		{
			//if (in_space_int(data, view->map.y, view->map.x + view->step.x))
			//{
				view->sideDist.x += view->deltaDist.x;
				view->map.x += view->step.x;
				side = 0;
				printf("aumentado x x: %d, y: %d deltaDist: x: %f y: %f\n", view->map.x, view->map.y, view->sideDist.x, view->sideDist.y);
			/*	
			}
			else
			{
				hit = 1;
				side = 0;
				printf("choque en x x: %d, y: %d\n", view->map.x, view->map.y);
			}
			*/
		}
		else
		{
			//if (in_space_int(data, view->map.y + view->step.y, view->map.x))
			//{
				view->sideDist.y += view->deltaDist.y;
				view->map.y += view->step.y;
				side = 1;
				printf("aumentado y x: %d, y: %d deltaDist: x: %f y: %f\n", view->map.x, view->map.y, view->sideDist.x, view->sideDist.y);
			/*
			}
			else
			{
				hit = 1;
				side = 1;
				printf("choque en y x: %d, y: %d\n", view->map.x, view->map.y);
			}
			*/
		}
		
		
		//printf("map x: %d y: %d\n", view->map.x, view->map.y);
		if (!in_space_int(data, view->map.y, view->map.x))
		{
			//printf("nevo x: %d y: %d\n", view->map.x, view->map.y);
			hit = 1;
		}
		
	}

	printf("choque x: %d y: %d\n", view->map.x, view->map.y);
	/*
	if (!side)
		perpWallDist = (view->map.x - pos.x + (1 - view->step.x) / 2) / view->rayDir.x;
	else
		perpWallDist = (view->map.y - pos.y + (1 - view->step.y) / 2) / view->rayDir.y;
	
	dest.x = (pos.x + (view->rayDir.x * perpWallDist)) * data->gamer->unitWidth;
	dest.y = (pos.y + (view->rayDir.x * perpWallDist)) * data->gamer->unitHeight;
	*/
	
	if (side)
	{
		dest.y = (view->map.y * data->gamer->unitHeight);
		
		double dist = fabs((data->gamer->position.y - dest.y) / view->rayDir.y);
		dest.x = data->gamer->position.x + (view->rayDir.x * dist);
		
	}
	else
	{
		dest.x = (view->map.x * data->gamer->unitWidth);
		double dist = fabs((data->gamer->position.x - dest.x) / view->rayDir.x);
		dest.y = data->gamer->position.y + (view->rayDir.y * dist);
	}
	
	printf("destino x: %f y: %f\n", dest.x, dest.y);
	if (dest.x >= 0 && dest.y >= 0 && dest.x < data->width && dest.y < data->height)
	//draw_circle(data, &data->window.img, dest, 5, color_int(0, 0, 255));
	   print_line(data, data->gamer->position, dest, color_int(0, 0, 255), &data->window.img);
	
}
/*
void old_load_view(t_file *data, int x)
{
	t_view *view;
	t_point dir;
	t_point pos;
	t_point *plane;
	int hit = 0;
	int side;
	t_point dest;
	char c;
	t_point dir1;

	pos = data->gamer->position;
	dir = data->gamer->direction;
	view = &data->view;
	plane = &data->gamer->plane;

	view->cameraX = 2 * x / (double)data->width - 1;
	view->rayDir.x = dir.x + plane->x * view->cameraX;
	view->rayDir.y = dir.y + plane->y * view->cameraX;
	dir1.x = data->gamer->position.x + (view->rayDir.x * 30);
	dir1.y = data->gamer->position.y + (view->rayDir.y * 30);
	print_line(data, pos, dir1, color_int(0,255,0), &data->window.img);
	view->map.x = pos.x / data->gamer->unitWidth;
	view->map.y = pos.y / data->gamer->unitHeight;
	//view->deltaDist.x = fabs(1 / view->rayDir.x);
	//view->deltaDist.y = fabs(1 / view->rayDir.y);
	view->deltaDist.x = sqrt(1 + (view->rayDir.y * view->rayDir.y) / (view->rayDir.x * view->rayDir.x));
	view->deltaDist.y = sqrt(1 + (view->rayDir.x * view->rayDir.x) / (view->rayDir.y * view->rayDir.y));
	if (view->rayDir.x < 0)
	{
		view->step.x = -1;
		view->sideDist.x = (pos.x - ((double)view->map.x * data->gamer->unitWidth));
		view->sideDist.x *=view->deltaDist.x;
	}
	else
	{
		view->step.x = 1;
		view->sideDist.x = (((double)view->map.x + 1) * data->gamer->unitWidth) - pos.x;
		view->sideDist.x *=view->deltaDist.x;
	}
	if (view->rayDir.y < 0)
	{
		view->step.y = -1;
		view->sideDist.y = pos.y - ((double)view->map.y * data->gamer->unitWidth);
		view->sideDist.y *=view->deltaDist.y;
	}
	else
	{
		view->step.y = 1;
		view->sideDist.y = (((double)view->map.y + 1) * data->gamer->unitWidth) - pos.y;
		view->sideDist.y *=view->deltaDist.y;
	}
	hit = 0;
	while (!hit && view->map.x < data->table->cols && view->map.y < data->table->rows && view->map.x > 0 && view->map.y >0)
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
		if (side)
		{
			dest.x = pos.x + (view->rayDir.x * view->sideDist.y);
			dest.y = pos.y + (view->rayDir.y * view->sideDist.y);
		}
		else
		{
			dest.x = pos.x + (view->rayDir.x * view->sideDist.x);
			dest.y = pos.y + (view->rayDir.y * view->sideDist.x);
		}
		
		//printf("map x: %d y: %d\n", view->map.x, view->map.y);
		if (data->table->table[view->map.y][view->map.x] != '0')
		{
			//printf("nevo x: %d y: %d\n", view->map.x, view->map.y);
			hit = 1;
		}
	}
	
	print_line(data, pos, dest, color_int(0, 0, 255), &data->window.img);
}
*/
int view_game(t_file *data)
{
	int x;    
	x = 0;
	
	printf("plane x: %f y: %f\n", data->gamer->plane.x, data->gamer->plane.y);
	while (x < 3)
	//while (x < data->width)
	{
		load_view(data, x);
		x++;
	}
	

	return (0);
}