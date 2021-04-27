/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:13:50 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/27 16:05:01 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <math.h>

//MAC

# define K_LEFT 0
# define K_RIGHT 2
# define K_UP 13
# define K_DOWN 1
# define K_TURN_L 123
# define K_TURN_R 124
# define K_MAP 46
# define K_ESC 53
# define EVENT_EXIT 17
# define K_NEXT 45

//LINUX
/*
#define K_LEFT 97
#define K_RIGHT 100
#define K_UP 119
#define K_DOWN 115
#define K_TURN_L 65361
#define K_TURN_R 65363
#define K_MAP 109
#define K_ESC 65307
#define EVENT_EXIT 33
#define K_NEXT 110
*/

enum e_dir
{
	North,
	South,
	East,
	West,
	Sprite,
	Life,
	GameOver,
	NextLevel,
	Blood,
	Beer,
	Size
};

typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_color;

typedef struct s_table
{
	int		cols;
	int		rows;
	char	**table;
}	t_table;

typedef struct s_point_int
{
	int	x;
	int	y;
}	t_point_int;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_sprite
{
	t_point			pos;
	double			dist;
	int				visible;
	struct s_sprite	*next;
	struct s_sprite	*pre;

}	t_sprite;

typedef struct s_list_sp
{
	t_sprite	*begin;
	t_sprite	*end;
	int			size;
}	t_list_sp;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_cont_img
{
	t_image		img;
	int			width;
	int			height;
	int			unitHeight;
	int			unitWidth;
	t_point_int	init;
}	t_cont_img;

typedef struct s_window
{
	void		*ptr;
	void		*win;
	t_cont_img	img;
}	t_window;

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	dir_side;
	t_point	plane;
	int		move_in_dir;
	int		move_in_side;
	int		rotate;
	int		unitWidth;
	int		unitHeight;
	int		act_map;
}	t_player;

typedef struct s_opt
{
	double	rot_speed;
	double	mov_speed;
	int		u_div;
	int		v_div;
	double	v_move;
}	t_opt;

typedef struct s_minimap
{
	t_point_int	init;
	t_point_int	init_table;
	t_point_int	end_table;
	int			size_map;
	int			width;
	int			height;
	int			unit_width;
	int			unit_height;
	int			color_walls;
	int			color_player;
	int			color_sprites;
	int			color_space;
}	t_minimap;

typedef struct s_bonus
{
	int		game;
	int		points;
	int		lives;
	int		len_bar;
	double	unit_bar;
	int		end;
	int		ending;
	int		blood;
	int		add_points;
	char	**maps;
	int		level;
	int		levels;
}	t_bonus;

typedef struct s_game
{
	int			to_save;
	int			width;
	int			height;
	char		player_init;
	t_player	*player;
	t_window	window;
	t_minimap	minimap;
	t_bonus		bonus;
	char		*t_NO;
	char		*t_SO;
	char		*t_WE;
	char		*t_EA;
	char		*sprite;
	t_color		*floor;
	t_color		*ceiling;
	t_table		table;
	t_opt		opt;
	t_cont_img	*text;
	t_list_sp	sprites;
	int			closed;
	int			has_moved;
	double		*wallDist;
}	t_game;

int			load_file(t_game *data, char *file);
void		handle_error(t_game *data, char *msg);
void		has_been_created(t_game *data, void *ptr);
void		check_file(t_game *data, char *file);
void		print_struct(t_game *data);
int			run_game(t_game *data);
int			event_exit(t_game *data);
void		set_point(t_point *point, double x, double y);
void		copy_point(t_point *dest, t_point src);
int			valid_point(t_game *data, int x, int y);
void		set_point_int(t_point_int *point, int x, int y);
t_sprite	*add_new_sp_back(t_game *data, t_list_sp *list, int x, int y);
void		free_components(t_game *data);
void		free_level(t_game *data);
void		check_wall_closed(t_game *data);
void		load_player(t_game *data, int y, int x);
void		draw_circle_map(t_game *data, t_point center, \
double radius, int color);
int			in_limits(t_point_int pos, t_point_int start, t_point_int end);
void		load_bmp(t_game *data);
void		load_next_level(t_game *data);

#endif