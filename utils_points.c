#include "includes/cub3d.h"

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