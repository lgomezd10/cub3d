#include "cub3d.h"

int press_key(int keycode, t_file *data)
{
	t_gamer *gamer;

	gamer = data->gamer;
	printf("press key: %d\n", keycode);
	if (keycode == K_LEFT)
		gamer->rotate = -1;
	if (keycode == K_RIGHT)
		gamer->rotate = 1;
	if (keycode == K_UP)
		gamer->move = -1;
	if (keycode == K_DOWN)
		gamer->move = 1;
	if (keycode == K_TURN_L)
		gamer->turn = -1;
	if (keycode == K_TURN_R)
		gamer->turn = 1;
	if (keycode == K_MAP)
	{
		gamer->act_map = !gamer->act_map;
		data->has_moved = 1;
	}
	if (keycode == K_ESC)
		event_exit(data);
	return (0);
}

int release_key(int keycode, t_file *data)
{
	t_gamer *gamer;

	gamer = data->gamer;
	printf("release key: %d\n", keycode);
	if (keycode == K_LEFT)
		gamer->rotate = 0;
	if (keycode == K_RIGHT)
		gamer->rotate = 0;
	if (keycode == K_UP)
		gamer->move = 0;
	if (keycode == K_DOWN)
		gamer->move = 0;
	if (keycode == K_TURN_L)
		gamer->turn = 0;
	if (keycode == K_TURN_R)
		gamer->turn = 0;
	return (0);
}

int event_exit(t_file *data)
{
	data->closed = 1;
	printf("VA A BORRAR COMPONENTES\n");
	free_components(data);
	exit(0);
	return (0);
}

