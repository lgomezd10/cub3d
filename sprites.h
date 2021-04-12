#ifndef SPRITES_H
# define SPRITES_H
# include "run_game.h"

typedef struct s_rc_sprites
{
    t_sprite *sprite;
	t_point pos_sp;
    t_point transf;
    double inv_det;
    int sp_screen_x;
    int v_mv_screen;
    int sp_height;
    int sp_width;
    t_point_int draw_start;
	t_point_int draw_end;
	t_point_int text;
} t_rc_sprites;

#endif