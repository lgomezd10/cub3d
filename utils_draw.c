#include "cub3d.h"

/*
mlx_hook(game.window.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.window.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
	mlx_hook(game.window.win, X_EVENT_EXIT, 0, &exit_hook, &game);
	mlx_loop_hook(game.window.ptr, &main_loop, &game);
	mlx_loop(game.window.ptr);
*/
/*
int
	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->move.x = 1;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->move.y = 1;
	if (keycode == KEY_A)
		game->x_move.x = 1;
	else if (keycode == KEY_D)
		game->x_move.y = 1;
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->rotate.x = 1;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->rotate.y = 1;
	return (0);
}

int
	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->move.x = 0;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->move.y = 0;
	else if (keycode == KEY_A)
		game->x_move.x = 0;
	else if (keycode == KEY_D)
		game->x_move.y = 0;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->rotate.x = 0;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->rotate.y = 0;
	else if (keycode == KEY_ESC)
		return (exit_game(game, EXIT_SUCCESS));
	else if (keycode == KEY_I)
		game->options = game->options ^ FLAG_UI;
	else if (keycode == KEY_L)
		game->options = game->options ^ FLAG_SHADOWS;
	else if (keycode == KEY_O)
		game->options = game->options ^ FLAG_CROSSHAIR;
	return (0);
}*/

void draw_circle(t_file *data, t_image *img, t_point center, double radius, int color)
{
    int i;
    int j;
    int to_y;
    int to_x;
    double distancia;

    i = center.y - radius;
    to_y = i + (2 * radius);
    while (i <= to_y)
    {
        j = center.x - radius;
        to_x = j + (2 * radius);
        while (j <= to_x)
        {
            distancia = (j - center.x) * (j - center.x) + (i - center.y) * (i - center.y);
            if (sqrt(distancia) <= radius)
                my_mlx_pixel_put(img, j, i, color);
            j++;
        }
        i++;
    }
}

void print_map(t_file *data, t_image *img)
{
    int i;
    int j;
    int x;
    int y;

    i = 0; 
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {        
           //y = i / unitHeight;
           //x = j / unitWidth;
        
           y = i / data->gamer->unitHeight;
           x = j / data->gamer->unitWidth;
           if (data->table->table[y][x] == '1')
            my_mlx_pixel_put(img, j, i, 0255255255);
           j++;
        }
        i++;
    }
}

void my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int press_key(int keycode, t_gamer *gamer)
{
    printf("key: %d\n", keycode);
    if (keycode == K_LEFT)
        gamer->move.x = -1;
    if (keycode == K_RIGHT)
        gamer->move.x = 1;
    if (keycode == K_UP)
        gamer->move.y = -1;
    if (keycode == K_DOWN)
        gamer->move.y = 1;
    if (keycode == K_ROT_L)
        gamer->rotate = -1;
    if (keycode == K_ROT_R)
        gamer->rotate = 1;
    return (0);
}

int release_key(int keycode, t_gamer *gamer)
{
    if (keycode == K_LEFT)
        gamer->move.x = 0;
    if (keycode == K_RIGHT)
        gamer->move.x = 0;
    if (keycode == K_UP)
        gamer->move.y = 0;
    if (keycode == K_DOWN)
        gamer->move.y = 0;
    if (keycode == K_ROT_L)
        gamer->rotate = 0;
    if (keycode == K_ROT_R)
        gamer->rotate = 0;
    return (0);
}



