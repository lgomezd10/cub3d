#include "includes/run_game.h"

int move_up(t_game *data)
{
    double new_x;
	double new_y;
    t_point dir;

    dir = data->player->dir_real;
    new_x = data->player->pos.x + (dir.x * data->opt.mov_speed);
    new_y = data->player->pos.y + (dir.y * data->opt.mov_speed);
    if (in_space(data, new_x, new_y))
    {
        data->player->pos.y = new_y;
        data->player->pos.x = new_x;
        return (1);
    }
    return (0);
}

int move_down(t_game *data)
{
    double new_x;
	double new_y;
    t_point dir;

    dir = data->player->dir_real;
    new_x = data->player->pos.x - (dir.x * data->opt.mov_speed);
    new_y = data->player->pos.y - (dir.y * data->opt.mov_speed);
    if (in_space(data, new_x, new_y))
    {
        data->player->pos.y = new_y;
        data->player->pos.x = new_x;
        return (1);
    }
    return (0);
}

void rotate_dir(t_game *data, t_point *dir, t_point *plane, int rot)
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
    copy_point(&data->player->dir, *dir);
    copy_point(&data->player->plane, *plane);
}

int turn_view(t_game *data)
{
    t_player *player;

    data->has_moved = 1;
    player = data->player;
    if (!player->is_turning)
    {
        player->is_turning = 1;
        copy_point(&player->dir_turn, player->dir_real);
        copy_point(&player->plane_turn, player->plane_real);
    }
    rotate_dir(data, &player->dir_turn, &player->plane_turn, player->turn);
    return (1);
}

int move(t_game *data)
{
    t_player *player;

    player = data->player;
    copy_point(&player->dir, player->dir_real);
    copy_point(&player->plane, player->plane_real);
    if (player->rotate || data->player->move)
    {
        data->player->is_turning = 0;    
        if (player->rotate)
            rotate_dir(data, &player->dir_real, &player->plane_real, player->rotate);
        if (data->player->move)
        {
            data->has_moved = 1;
            if (data->player->move == -1)
                move_up(data);
            if (data->player->move == 1)
                move_down(data);
        }
    }
    if (data->player->turn)
    {
        turn_view(data);
    }
	return (data->has_moved);
}