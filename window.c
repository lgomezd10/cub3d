#include "cub3d.h"

int init_window(t_file *data)
{
    int init;
    /*
    data->opt.mov_speed = 0.11;
    data->opt.rot_speed = 0.11;
    data->map.height = data->height / 3 - 10;
    data->map.width = data->width - 10;
    data->map.unitHeight = data->map.height / data->table->rows;
    data->map.unitWidth = data->map.width / data->table->cols;
    */
    
    data->opt.mov_speed = 0.11;
    data->opt.rot_speed = 0.11;    
    data->map.width = (data->width / 3);    
    data->map.height = data->map.width * 9 / 16; 
    printf("resolucion ancho: %d alto %d", data->map.width, data->map.height);
    data->map.unitHeight = data->map.height / data->table->rows;
    data->map.unitWidth = data->map.width / data->table->cols;
    init = ((data->width / 3) * 2) - 1;    
    set_point_int(&data->map.init, init, 0);
    data->window.img.height = data->height;
    data->window.img.width = data->width;
    data->window.img.unitHeight = data->window.img.height / data->table->rows;
    data->window.img.unitWidth = data->window.img.width / data->table->cols;
    set_point_int(&data->window.img.init, 0, 0);
    data->window.ptr = mlx_init();
    data->window.win = mlx_new_window(data->window.ptr, data->width, data->height, "CUB3D");
    printf("iniciada venta\n");
    return (0); 
}

int load_img(t_file *data, t_cont_img *img)
{
    void *ptr;

    printf("hola 1 \n");
    ptr = mlx_init();
    img->img.img = mlx_png_file_to_image(data->window.ptr, data->t_NO, &img->width, &img->height);
    //img->img.img = mlx_xpm_file_to_image(data->window.ptr, data->t_NO, &img->width, &img->height);
    printf("hola 2\n");
    //img->img.addr = mlx_get_data_addr(img->img.img, &img->img.bits_per_pixel, &img->img.line_length, &img->img.endian);
    printf("hola 3\n");
    printf("cod north: %d dimensiones texturas alto: %d, ancho %d\n", North, img->width, img->height);
    return (0);
}

int init_texture(t_file *data)
{
    t_cont_img *text;
    int fd;

    printf("valor de size %d\n", Size);
    text = (t_cont_img *)ft_calloc(sizeof(t_texture), Size);
    fd = open(data->t_NO, O_RDONLY);
    printf("fichero abierto: %d\n", fd);
    close(fd);
    load_img(data, &text[North]);
    return (0);
}