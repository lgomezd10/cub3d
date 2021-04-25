#include "../../includes/bonus.h"
/*
int transparency_color(t_game *data, int color, t_point_int pos, double div)
{
    int new;
    int cimg;
    t_cont_img *img;
    int r;
    int g;
    int b;

    new = color;
    if (div > 1)
    {
        img = &data->window.img;
        cimg = color = my_mlx_pixel_get(img, pos.x, pos.y);
        r = (get_red(color) / div) + (get_red(cimg) / div);
        g = (get_green(color) / div) + (get_green(cimg) / div);
        b = (get_blue(color) / div) + (get_blue(cimg) / div);
        new = color_int(r, g, b);
    }
    return (new);
}
*/
int transparency_color(int color, double div)
{
    int new;
    int r;
    int g;
    int b;

    
    new = color;
    if (div > 1)
    {        
        r = get_red(color);
        g = get_green(color);
        b = get_blue(color);
        new = get_color(80, r, g, b);
    }
    return (new);
}

int get_trans(int color)
{
    return ((color & 0xFF000000) >> 24);
}

int get_red(int color)
{
    return ((color & 0x00FF0000) >> 16);
}

int get_green(int color)
{
    return ((color & 0x0000FF00) >> 24);
}

int get_blue(int color)
{
    return (color & 0xFF);
}

int get_color(int t, int r, int g, int b)
{
    return ((t << 24) + (r << 16) + (g << 8) + b);
}