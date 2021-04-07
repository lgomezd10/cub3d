#ifndef SHOW_H
#define SHOW_H
#include "cub3d.h"

typedef struct s_view
{
    double cameraX;
    t_point rayDir;
    t_point_int map;
    t_point sideDist;
    t_point deltaDist;
    double perpWaDist;
    t_point step_ray;
    int side;
    int lineHeight;
    int drawStart;
	int drawEnd;
    t_point begin;
	t_point end;
    double wallX;
	t_point text;
	double step;
	double textPos;
    int color;
} t_view;

#endif