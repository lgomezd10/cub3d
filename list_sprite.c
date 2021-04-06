#include "cub3d.h"

t_sprite *add_new_sp_back(t_list_sp *list, int x, int y)
{
    t_sprite *new;

    new = (t_sprite *)ft_calloc(sizeof(t_sprite), 1);
    if (new)
    {
        new->pos.x = x + 0.5;
        new->pos.y = y + 0.5;
        if (!list->begin)
        {
            list->begin = new;
            list->end = new;
            list->size = 1;
            return (new);
        }
        new->pre = list->end;
        list->end = new;
        list->size++;
    }
    else
        ft_errors("Error al crear sprite");    
    return (new);
}

void load_dist_sp(t_file *data)
{
    t_point pos;
    t_point pos_sp;
    t_sprite *sprite;

    pos = data->gamer->position;
    pos_sp = sprite->pos;
    sprite = data->sprites.begin;
    // TODO quitar error por si no hay sprite
    if (!sprite)
        ft_errors("No se han cargado los sprites");
    while (sprite)
    {
        sprite->dist = (pos.x - pos_sp.x) * (pos.x - pos_sp.x) + (pos.y - pos_sp.y) * (pos.y - pos_sp.y);
        sprite = sprite->next;
    }
}

void short_sprites(t_file *data)
{
    double min;
    double max;
    t_list_sp *list;
    t_sprite *sprites;

    load_dist_sp(data);
    list = &data->sprites;
    sprites = list->begin;
    while (sprites)
    {
        if (sprites->dist > max)
        {
            sprites->pre->next = sprites->next;
            sprites->next = list->begin;
            list->begin = sprites;
            max = sprites->dist;
        }
        else if (sprites->dist < min)
        {
            sprites->next->pre = sprites->pre;
            sprites->next = list->begin;
            list->begin = sprites;
            max = sprites->dist;
        }

    }

}