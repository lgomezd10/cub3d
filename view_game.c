#include "cub3d.h"

void load_view(t_file *data, int x)
{
    t_view *view;
    t_point dir;
    t_point pos;
    t_point *plane;    

    pos = data->gamer->position;
    dir = data->gamer->direction;
    view = &data->view;
    plane = &data->view.plane;

    view->cameraX = 2 * x / (double)data->width - 1;
    view->rayDir.x = dir.x + plane->x * view->cameraX;
    view->rayDir.y = dir.y + plane->y * view->cameraX;
    view->map.x = dir.x / data->gamer->unitWidth;
    view->map.y = dir.y / data->gamer->unitHeight;

    if (view->rayDir.x < 0)
    {
        view->step.x = -1;
        view->sideDist.x = pos.x - ((double)((int)pos.x/ (int)data->gamer->unitWidth) * data->gamer->unitWidth);
    }
    else
    {
        view->step.x = 1;
        view->sideDist.x = pos.x + data->gamer->unitWidth - ((double)((int)pos.x/ (int)data->gamer->unitWidth) * data->gamer->unitWidth);
    }
    if (view->rayDir.y < 0)
    {
        view->step.y = -1;
        view->sideDist.y = pos.y - ((double)((int)pos.y/ (int)data->gamer->unitWidth) * data->gamer->unitWidth);
    }
    else
    {
        view->step.x = 1;
        view->sideDist.x = pos.x + data->gamer->unitWidth - ((double)((int)pos.x/ (int)data->gamer->unitWidth) * data->gamer->unitWidth);
    }
}

int view_game(t_file *data)
{
    int x;

    data->view.plane.x = 0;
    data->view.plane.y = 0.66;
    x = 0;
    while (x < data->width)
    {
        load_view(data, x);
        x++;
    }
    

    return (0);
}