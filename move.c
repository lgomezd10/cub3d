#include "cub3d.h"

int move_up(t_file *data)
{
    double new_x;
	double new_y;
    t_point dir;

    dir = data->gamer->direction;
    new_x = data->gamer->position.x + (dir.x);
    new_y = data->gamer->position.y + (dir.y);
    if (in_space(data, new_y, new_x))
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
    new_x = data->gamer->position.x - (dir.x);
    new_y = data->gamer->position.y - (dir.y);
    if (in_space(data, new_y, new_x))
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

	rot = .11;
	rotate = data->gamer->rotate;
	has_move = 0;
	dir = data->gamer->direction;    
	if (rotate)
	{		
		data->gamer->direction.x = dir.x * cos(rotate * rot) - dir.y * sin(rotate * rot);
		data->gamer->direction.y = dir.x * sin(rotate * rot) + dir.y * cos(rotate * rot);
		has_move = 1;		
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