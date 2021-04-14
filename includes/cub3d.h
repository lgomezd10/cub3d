#ifndef CUB3D_H
#define CUB3D_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"
#include "includes/mlx_png.h"
#include "libft/libft.h"
#include <math.h>

#define ROTATE_SPEED .11
#define MOVE_SPEED .11


//MAC
/*
#define K_LEFT 0
#define K_RIGHT 2
#define K_UP 13
#define K_DOWN 1
#define K_TURN_L 123
#define K_TURN_R 124
#define K_MAP 46
#define K_ESC 65307
#define EVENT_EXIT 17
*/

//LINUX


#define K_LEFT 97
#define K_RIGHT 100
#define K_UP 119
#define K_DOWN 115
#define K_TURN_L 65361
#define K_TURN_R 65363
#define K_MAP 109
#define K_ESC 65307
#define EVENT_EXIT 33


enum DIR
{
    North,
    South,
    East,
    West,
    Sprite,
    Size
};

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

typedef struct s_sprite
{
    t_point pos;    
    double dist;
    int visible;
    struct s_sprite *next;
    struct s_sprite *pre;

} t_sprite;

typedef struct s_list_sp
{
    t_sprite *begin;
    t_sprite *end;
    int size;
} t_list_sp;

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


typedef struct s_player
{
    t_point pos;
    t_point dir;
    t_point plane;
    t_point dir_real;
    t_point plane_real;
    t_point dir_turn;
    t_point plane_turn;
    int move;
    int rotate;
    int turn;
    int is_turning;
    int unitWidth;
    int unitHeight;
    int act_map;
} t_player;

typedef struct s_wall
{
    t_point *up_right;
    t_point *up_left;
    t_point *down_right;
    t_point *down_left;
} t_wall;



typedef struct s_opt
{
    double rot_speed;
    double mov_speed;
    int u_div;
    int v_div;
    double v_move;
} t_opt;

typedef struct s_minimap
{
    t_point_int init;
    int width;
    int height;
    int unit_width;
    int unit_height;
    int color_walls;
    int color_player;
    int color_sprites;
    int color_space;
} t_minimap;


typedef struct s_game
{
    int to_save;
    int width;
    int height;
    char player_init;
    t_player *player;
    t_window window;
    t_minimap minimap;
    char *t_NO;
    char *t_SO;
    char *t_WE;
    char *t_EA;
    char *sprite;
    t_color *floor;
    t_color *ceiling;
    t_table table;
    t_opt opt;
    t_cont_img *text;
    t_list_sp sprites;
    int closed;
    int has_moved;
    double wallDist[1920];
} t_game;

int load_file(char *file, t_game *data);
void ft_errors(char *msg);
void has_been_created(void *ptr);
void print_struct(t_game *data);
int run_game(t_game *data);
int event_exit(t_game *data);
void set_point(t_point *point, double x, double y);
void copy_point(t_point *dest, t_point src);
void set_point_int(t_point_int *point, int x, int y);
t_sprite *add_new_sp_back(t_list_sp *list, int x, int y);
void free_components(t_game *data);
void check_wall_closed(t_game *data);
void load_player(t_game *data, int y, int x);

#endif