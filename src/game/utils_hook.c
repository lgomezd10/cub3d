#include "../../includes/cub3d.h"

int press_key(int keycode, t_game *data)
{
	t_player *player;

	player = data->player;
	printf("press key: %d\n", keycode);
	if (keycode == K_LEFT)
		player->rotate = -1;
	if (keycode == K_RIGHT)
		player->rotate = 1;
	if (keycode == K_UP)
		player->move = -1;
	if (keycode == K_DOWN)
		player->move = 1;
	if (keycode == K_TURN_L)
		player->turn = -1;
	if (keycode == K_TURN_R)
		player->turn = 1;
	if (keycode == K_MAP)
	{
		player->act_map = !player->act_map;
		data->has_moved = 1;
	}
	if (keycode == K_ESC)
		event_exit(data);
	return (0);
}

int release_key(int keycode, t_game *data)
{
	t_player *player;

	player = data->player;
	printf("release key: %d\n", keycode);
	if (keycode == K_LEFT)
		player->rotate = 0;
	if (keycode == K_RIGHT)
		player->rotate = 0;
	if (keycode == K_UP)
		player->move = 0;
	if (keycode == K_DOWN)
		player->move = 0;
	if (keycode == K_TURN_L)
		player->turn = 0;
	if (keycode == K_TURN_R)
		player->turn = 0;
	return (0);
}

int event_exit(t_game *data)
{
	data->closed = 1;
	printf("VA A BORRAR COMPONENTES\n");
	free_components(data);
	system("leaks cub3D");
	exit(0);
	return (0);
}

