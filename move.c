#include "cub3d.h"

void set_point(t_point *point, double x, double y)
{
    point->x = x;
    point->y = y;
}

void copy_point(t_point *dest, t_point src)
{
    dest->x = src.x;
    dest->y = src.y;
}

void set_point_int(t_point_int *point, int x, int y)
{
    point->x = x;
    point->y = y;
}
int move_up(t_file *data)
{
    double new_x;
	double new_y;
    t_point dir;

    dir = data->gamer->dir_real;
    new_x = data->gamer->pos.x + (dir.x * data->opt.mov_speed);
    new_y = data->gamer->pos.y + (dir.y * data->opt.mov_speed);
    if (in_space(data, new_x, new_y))
    {
        data->gamer->pos.y = new_y;
        data->gamer->pos.x = new_x;
        return (1);
    }
    return (0);
}

int move_down(t_file *data)
{
    double new_x;
	double new_y;
    t_point dir;

    dir = data->gamer->dir_real;
    new_x = data->gamer->pos.x - (dir.x * data->opt.mov_speed);
    new_y = data->gamer->pos.y - (dir.y * data->opt.mov_speed);
    if (in_space(data, new_x, new_y))
    {
        data->gamer->pos.y = new_y;
        data->gamer->pos.x = new_x;
        return (1);
    }
    return (0);
}

void rotate_dir(t_file *data, t_point *dir, t_point *plane, int rot)
{
    t_point dir_old;
    t_point plane_old;
    double speed;

    data->has_moved = 1;
    dir_old = *dir;
    plane_old = *plane;
    speed = data->opt.rot_speed;
    dir->x = dir_old.x * cos(rot * speed) - dir_old.y * sin(rot * speed);
    dir->y = dir_old.x * sin(rot * speed) + dir_old.y * cos(rot * speed);
    plane->x = plane_old.x * cos(rot * speed) - plane_old.y * sin(rot * speed);
    plane->y = plane_old.x * sin(rot * speed) + plane_old.y * cos(rot * speed);
    copy_point(&data->gamer->dir, *dir);
    copy_point(&data->gamer->plane, *plane);
}

int turn_view(t_file *data)
{
    t_gamer *gamer;

    data->has_moved = 1;
    gamer = data->gamer;
    if (!gamer->is_turning)
    {
        gamer->is_turning = 1;
        copy_point(&gamer->dir_turn, gamer->dir_real);
        copy_point(&gamer->plane_turn, gamer->plane_real);
    }
    rotate_dir(data, &gamer->dir_turn, &gamer->plane_turn, gamer->turn);
    return (1);
}

int move(t_file *data)
{
	double speed;
    t_gamer *gamer;

    gamer = data->gamer;
	speed = data->opt.rot_speed;
    copy_point(&gamer->dir, gamer->dir_real);
    copy_point(&gamer->plane, gamer->plane_real);
    if (gamer->rotate || data->gamer->move)
        data->gamer->is_turning = 0;
	if (gamer->rotate)
		rotate_dir(data, &gamer->dir_real, &gamer->plane_real, gamer->rotate);
	if (data->gamer->move)
	{
        data->has_moved = 1;
		if (data->gamer->move == -1)
            move_up(data);
		if (data->gamer->move == 1)
            move_down(data);
	}
    if (data->gamer->turn)
        turn_view(data);
	return (data->has_moved);
}