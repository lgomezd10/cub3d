#include "cub3d.h"

void free_table(t_file *data)
{
    int i;

    i = 0;
    while (i < data->table.rows)
    {
        free(data->table.table[i]);
        data->table.table[i] = 0;
        i++;
    }
    free(data->table.table);
    data->table.table = 0;
}



void clear_window(t_file *data)
{
    int i;

    i = 0;
    while (i < Size)
    {
        if (data->text[i].img.img)
        {
            mlx_destroy_image(data->window.ptr, data->text[i].img.img);
            data->text[i].img.img = 0;
        }
        i++;
    }
    if (data->window.img.img.img)
    {
        mlx_destroy_image(data->window.ptr, data->window.img.img.img);
        data->window.img.img.img = 0;
    }
    if (data->map.img.img)
    {
        mlx_destroy_image(data->window.ptr, data->map.img.img);
        data->map.img.img = 0;
    }
    if (data->window.ptr && data->window.win)
    {
        mlx_destroy_window(data->window.ptr, data->window.win);
        data->window.win = 0;
        data->window.ptr = 0;
    }
}

void clear_sprites(t_file *data)
{
    t_sprite *sprite;
    t_sprite *temp;

    sprite = data->sprites.begin;
    while (sprite)
    {
        temp = sprite;
        sprite = sprite->next;
        free(temp);
    }
}

void free_components(t_file *data)
{
    free_table(data);
    free(data->t_NO);
    data->t_NO = 0;
    free(data->t_SO);
    data->t_SO = 0;
    free(data->t_WE);
    data->t_WE = 0;
    free(data->t_EA);
    data->t_EA = 0;
    free(data->sprite);
    data->sprite = 0;
    free(data->ceiling);
    data->ceiling = 0;
    free(data->floor);
    data->floor = 0;
    free(data->gamer);    
    data->gamer = 0;
    clear_window(data);
    free(data);
}