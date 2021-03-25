#include "cub3d.h"

int press_key(int keycode, t_gamer *gamer)
{
	printf("press key: %d\n", keycode);
	if (keycode == K_LEFT)
		gamer->rotate = -1;
	if (keycode == K_RIGHT)
		gamer->rotate = 1;
	if (keycode == K_UP)
		gamer->move = -1;
	if (keycode == K_DOWN)
		gamer->move = 1;
	return (0);
}

int release_key(int keycode, t_gamer *gamer)
{
	printf("release key: %d\n", keycode);
	if (keycode == K_LEFT)
		gamer->rotate = 0;
	if (keycode == K_RIGHT)
		gamer->rotate = 0;
	if (keycode == K_UP)
		gamer->move = 0;
	if (keycode == K_DOWN)
		gamer->move = 0;
	return (0);
}

int event_exit(int keycode, t_gamer *gamer)
{
    exit(0);
}

int in_space(t_file *data, double y, double x)
{
	int i;
	int j;
	int is_space;

	i = y / data->gamer->unitHeight;
	j = x / data->gamer->unitWidth;
	is_space = y >= 0 && y < (double)data->height;
	is_space = is_space && x >= 0 && x < (double)data->width;
	is_space = is_space && data->table->table[i][j] == '0';
	return (is_space);
}