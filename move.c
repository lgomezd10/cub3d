#include "cub3d.h"

void set_point(t_point *point, double x, double y)
{
    point->x = x;
    point->y = y;
}
int move_up(t_file *data)
{
    double new_x;
	double new_y;
    t_point dir;

    dir = data->gamer->direction;
    new_x = data->gamer->position.x + (dir.x * data->opt.mov_speed);
    new_y = data->gamer->position.y + (dir.y * data->opt.mov_speed);
    if (in_space(data, new_x, new_y))
    {
        data->gamer->position.y = new_y;
        data->gamer->position.x = new_x;
        return (1);
    }
    return (0);
}

int move_down(t_file *data)
{
    double new_x;
	double new_y;
    t_point dir;

    dir = data->gamer->direction;
    new_x = data->gamer->position.x - (dir.x * data->opt.mov_speed);
    new_y = data->gamer->position.y - (dir.y * data->opt.mov_speed);
    if (in_space(data, new_x, new_y))
    {
        data->gamer->position.y = new_y;
        data->gamer->position.x = new_x;
        return (1);
    }
    return (0);
}

int move(t_file *data)
{
	int rotate;
	int has_move;
	double rot;
	t_point dir;
    t_point plane;

	rot = data->opt.rot_speed;
	rotate = data->gamer->rotate;
	has_move = 0;
	dir = data->gamer->direction;
    plane = data->gamer->plane;
    
	if (rotate)
	{		
		data->gamer->direction.x = dir.x * cos(rotate * rot) - dir.y * sin(rotate * rot);
		data->gamer->direction.y = dir.x * sin(rotate * rot) + dir.y * cos(rotate * rot);
        data->gamer->plane.x = plane.x * cos(rotate * rot) - plane.y * sin(rotate * rot);
        data->gamer->plane.y = plane.x * sin(rotate * rot) + plane.y * cos(rotate * rot);
		has_move = 1;
        printf("new direction x: %f, y %f\n", data->gamer->direction.x, data->gamer->direction.y);	
	}
	if (data->gamer->move)
	{
		if (data->gamer->move == -1)
            has_move = move_up(data);
		if (data->gamer->move == 1)
            has_move = move_down(data) || has_move;		
	}
	return (has_move);
}