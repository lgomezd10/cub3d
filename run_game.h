#ifndef RUN_GAME_H
#define RUN_GAME_H
#include "cub3d.h"


void short_sprites(t_file *data);
void print_minimap(t_file *data);
void init_minimap(t_file *data);
int init_texture(t_file *data);
void print_line(t_file *data, t_point from, t_point to, int color, t_cont_img *img);
void print_line_real(t_file *data, int x, int start, int end, int color, t_cont_img *img);
void print_cel_floor(t_file *data, int ceiling, int floor, t_cont_img *img);
int raycaster(t_file *data);
void draw_circle(t_file *data, t_cont_img *img, t_point center, double radius, int color);
int press_key(int keycode, t_file *data);
int release_key(int keycode, t_file *data);
void my_mlx_pixel_put(t_cont_img *data, int x, int y, int color);
int init_window(t_file *data);
void print_map(t_file *data, t_cont_img *img);
void	print_sprites(t_file *data);

#endif