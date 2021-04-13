#include "run_game.h"

void load_window(t_file *data)
{    
    t_point_int size;

    set_point_int(&data->window.img.init, 0, 0);
    data->window.ptr = mlx_init();
    mlx_get_screen_size(data->window.ptr, &size.x, &size.y);
    if (data->width > size.x || data->height > size.y)
    {
        data->width = size.x;
        data->height = size.y;
    }
    data->window.img.width = data->width;
    data->window.img.height = data->height;
    
    data->window.img.unitHeight = data->window.img.height / data->table.rows;
    data->window.img.unitWidth = data->window.img.width / data->table.cols;
    printf("El tamaño de la pantalla es ancho: %d, alto: %d\n", size.x, size.y);
    data->window.win = mlx_new_window(data->window.ptr, data->width, data->height, "CUB3D");
    printf("iniciada venta\n");
}

int init_window(t_file *data)
{
    int init;

    data->opt.mov_speed = 0.11;
    data->opt.rot_speed = 0.11;   
    data->opt.u_div = 1;
    data->opt.v_div = 1;
    data->opt.v_move = 0.0;
    load_window(data);
    init_minimap(data);
    return (0);
}

int load_img(t_file *data, t_cont_img *img, int dir)
{
    void *ptr;
    char *str;

    if (dir == North)
        str = data->t_NO;
    if (dir == South)
        str = data->t_SO;
    if (dir == East)
        str = data->t_EA;
    if (dir == West)
        str = data->t_WE;
    if (dir == Sprite)
        str = data->sprite;
    ptr = mlx_init();
    img->img.img = mlx_xpm_file_to_image(data->window.ptr, str, &img->width, &img->height);
    img->img.addr = mlx_get_data_addr(img->img.img, &img->img.bits_per_pixel, &img->img.line_length, &img->img.endian);
    return (0);
}

int init_texture(t_file *data)
{
    t_cont_img *text;
    int fd;

    printf("valor de size %d\n", Size);
    text = (t_cont_img *)ft_calloc(sizeof(t_cont_img), Size);
    has_been_created(text);
    fd = open(data->t_NO, O_RDONLY);
    printf("fichero abierto: %d\n", fd);
    close(fd);
    load_img(data, &text[North], North);
    load_img(data, &text[South], South);
    load_img(data, &text[East], East);
    load_img(data, &text[West], West);
    load_img(data, &text[Sprite], Sprite);
    data->text = text;
    return (0);
}