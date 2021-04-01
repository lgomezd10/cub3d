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
	hit = 0;
	while (!hit)
	{
		if (view->sideDist.x < view->sideDist.y)
		{
			if (in_space_int(data, view->map.x + view->step.x, view->map.y))
			{
				view->sideDist.x += view->deltaDist.x;
				view->map.x += view->step.x;
				side = 0;
			}
			else
			{
				hit = 1;
				side = 0;
			}
		}
		else
		{
			if (in_space_int(data, view->map.x, view->map.y + view->step.y))
			{
				view->sideDist.y += view->deltaDist.y;
				view->map.y += view->step.y;
				side = 1;
			
			}
			else
			{
				hit = 1;
				side = 1;
			}
		}		
	}

	if (side)
	{
		dest.y = view->map.y;
		if (view->rayDir.y > 0)
			dest.y++;				
		double dist = fabs((pos.y - dest.y) / view->rayDir.y);
		dest.x = pos.x + (view->rayDir.x * dist);
		
	}
	else
	{
		dest.x = view->map.x;
		if (view->rayDir.x > 0)
			dest.x++;
		double dist = fabs((pos.x - dest.x) / view->rayDir.x);
		dest.y = pos.y + (view->rayDir.y * dist);
	}
	if (dest.x >= 0 && dest.y >= 0 && dest.x < data->width && dest.y < data->height)
	   print_line(data, pos, dest, color_int(0, 0, 255), &data->window.img);
	
}

int view_game(t_file *data)
{
	int x;    
	x = 0;
	
	printf("plane x: %f y: %f\n", data->gamer->plane.x, data->gamer->plane.y);
	//while (x < 3)
	while (x < data->width)
	{
		load_view(data, x);
		x++;
	}
	

	return (0);
}