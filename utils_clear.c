#include "cub3d.h"

void clear_window(t_file *data)
{
    int i;

    i = 0;
    while (i < Size)
    {
        if (data->text[i].img.img)
            mlx_destroy_image(data->window.ptr, data->text[i].img.img);
    }
    if (data->window.img.img.img)
        mlx_destroy_image(data->window.ptr, data->window.img.img.img);
    if (data->map.img.img)
        mlx_destroy_image(data->window.ptr, data->map.img.img);
    if (data->window.ptr && data->window.win)
        mlx_destroy_window(data->window.ptr, data->window.win);
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