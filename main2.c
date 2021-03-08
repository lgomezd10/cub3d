#include <mlx.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int     x;
    int     x2;
    int     y;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    
    y = 100;
    while (y < 500)
    {
        x = 100;
        while (x < 700)
        {
            my_mlx_pixel_put(&img, x, y, 0x00FF0000);
            x *= y;
        }
        y++;
    }
    
    y = 100;
    x = 1000;
    x2 = 1;
    while (y < 300)
    {
        
        while (x <= 600 + x2 && x < 1000)
        {
            my_mlx_pixel_put(&img, x, y, 0x00FF0000);
            x++;
        }
        y++;
        x2++;
        x = 600 - x2;
        
    }
                   
    
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}