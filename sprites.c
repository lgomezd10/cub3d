#include "cub3d.h"

void print_sprites(t_file *data)
{
    t_sprite *sprite;
    t_point pos_sp;
    t_point pos;
    double invDet;
    t_gamer *gamer;
    t_point trans;
    int sp_screenx;

    sprite = data->sprites.begin;
    pos = data->gamer->pos;
    gamer = data->gamer;
    while (sprite)
    {
        pos_sp.x = sprite->pos.x - pos.x;
        pos_sp.y = sprite->pos.y - pos.y;
        invDet = 1.0 / (gamer->plane.x * gamer->dir.y - gamer->dir.x * gamer->plane.y);

        trans.x = invDet * (gamer->dir.y * pos_sp.x - gamer->dir.x * pos_sp.y);
        trans.y = invDet * (-gamer->plane.y * pos_sp.x - gamer->plane.x * pos_sp.y);

        sp_screenx = (data->width / 2) * (1 + trans.x / trans.y);


        sprite = sprite->next;
    }

}