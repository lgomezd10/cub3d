#ifndef CUB3D_H
#define CUB3D_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include "libft/libft.h"
#include <math.h>

#define ROTATE_SPEED .11
#define MOVE_SPEED .11
#define EVENT_EXIT 17

//MAC
/*
#define K_LEFT 0
#define K_RIGHT 2
#define K_UP 13
#define K_DOWN 1
#define K_ROT_L 123
#define K_ROT_R 124
*/

//LINUX

#define K_LEFT 97
#define K_RIGHT 100
#define K_UP 119
#define K_DOWN 115
#define K_ROT_L 65361
#define K_ROT_R 65363
#define K_MAP 109

typedef struct s_color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} t_color;

typedef struct s_table
{
    int cols;
    int rows;
    char **table;
}   t_table;

typedef struct s_point_int
{
    int x;
    int y;
} t_point_int;

typedef struct s_point
{
    double x;
    double y;
} t_point;

typedef struct s_image
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
} t_image;

typedef struct s_cont_img
{
    t_image img;
    int width;
    int height;
    int unitHeight;
    int unitWidth;
    t_point_int init;
} t_cont_img;


typedef struct s_window
{
    void *ptr;
    void *win;
    t_cont_img img;
} t_window;

typedef struct s_map
{
    
} t_map;

typedef struct s_gamer
{
    t_point position;
    t_point direction;
    t_point plane;
    int move;
    int rotate;
    int unitWidth;
    int unitHeight;
    int act_map;
} t_gamer;

typedef struct s_wall
{
    t_point *up_right;
    t_point *up_left;
    t_point *down_right;
    t_point *down_left;
} t_wall;

typedef struct s_view
{
    double cameraX;
    t_point rayDir;
    t_point_int map;
    t_point sideDist;
    t_point deltaDist;
    double perpWaDist;
    t_point step;
} t_view;

typedef struct s_opt
{
    double rot_speed;
    double mov_speed;

} t_opt;
typedef struct s_file
{
    int width;
    int height;
    char gamer_init;
    t_gamer *gamer;
    t_view view;
    t_window window;
    t_cont_img map;
    char *t_NO;
    char *t_SO;
    char *t_WE;
    char *t_EA;
    char *sprite;
    t_color *floor;
    t_color *ceiling;
    t_table *table;
    t_opt opt;
} t_file;

int load_file(char *file, t_file *data);
void ft_errors(char *msg);
int correct_line_map(char *str, t_file *data);
int data_loaded(t_file *data);
void load_gamer(t_file *data, int y, int x, char pos);
int get_map(int fd, char *str, t_file *data);
void print_struct(t_file *data);
void wall_connected(t_file *data);
void paint_map(t_file *data);
void draw_circle(t_file *data, t_cont_img *img, t_point center, double radius, int color);
int press_key(int keycode, t_gamer *gamer);
int release_key(int keycode, t_gamer *gamer);
void my_mlx_pixel_put(t_cont_img *data, int x, int y, int color);
int init_window(t_file *data);
void print_map(t_file *data, t_cont_img *img);
int print_image(t_file *data);
void paint_map_antiguo(t_file *data);
int load_image(t_file *data);
int in_space(t_file *data, double x, double y);
int in_space_int(t_file *data, int x, int y);
int move(t_file *data);
int color_int(int red, int green, int blue);
int event_exit(int keycode, t_gamer *gamer);
void print_line(t_file *data, t_point from, t_point to, int color, t_cont_img *img);
int view_game(t_file *data);
void set_point(t_point *point, double x, double y);
void set_point_int(t_point_int *point, int x, int y);
char get_value(t_file *data, t_point pos, t_point dir);
void print_line_real(t_file *data, int x, int start, int end, int color, t_cont_img *img);
void print_cel_floor(t_file *data, int ceiling, int floor, t_cont_img *img);
#endif