#ifndef SHOW_H
#define SHOW_H
#include "run_game.h"

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

int	find_hit(t_file *data, t_view *view);
t_cont_img	*select_text(t_file *data, t_view *view);
#endif