#include "includes/run_game.h"

// 54 + 4 * width * height

void save_as_char(unsigned char *str, int nbr)
{
    str[0] = (unsigned char)(nbr);
	str[1] = (unsigned char)(nbr >> 8);
	str[2] = (unsigned char)(nbr >> 16);
	str[3] = (unsigned char)(nbr >> 24);
}

void write_header(t_game *data, int fd, int file_size)
{
    unsigned char *header;
    //int file_size;

    //filesize = 54 + 4 * data->width * data->height;
    header = ft_calloc(sizeof(char), 54);
    has_been_created(header);
    header[0] = (unsigned char)('B');
    header[1] = (unsigned char)('M');
    save_as_char(&header[2], file_size);
    /*
    save_as_char(&header[10], 54);
    save_as_char(&header[14], 40);
    */
    header[10] = (unsigned char)54;
    header[14] = (unsigned char)40;
    save_as_char(&header[18], data->width);
    save_as_char(&header[22], data->height);
    header[27] = (unsigned char)1;
    header[28] = (unsigned char)24;
    if (write(fd, header, 54) < 0)
        ft_errors("Error to write screenshop.bmp");
    free(header);
    header = 0;
}

void write_image(t_game *data, int fd, int pad)
{
    int x;
    int y;
    int color;

    y = data->height;
    while (y >= 0)
    {
        x = data->width - 1;
        while (x >= 0)
        {
            color = my_mlx_pixel_get(&data->window.img, x, y);
            if (write(fd, &color, 3) < 0)
                ft_errors("Error to write screenshop.bmp");
            if (write(fd, "\0\0\0", pad) < 0)
                ft_errors("Error to write screenshop.bmp");
            x--;
        }
        y--;
    }
}

void save_bmp(t_game *data)
{
    int fd;
    int pad;
    int file_size;

    pad = (4 - (data->width * 3) % 4) % 4;
    file_size = 54 + (3 * (data->width + pad) * data->height);
    //fd = open("screenshop.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND);
    fd = open("screenshop.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,  0644);
    if (fd < 0)
        ft_errors("Can't open screenshop.bmp");
    write_header(data, fd, file_size);
    write_image(data, fd, pad);
    close(fd);
    printf("Se ha terminado de guardar la imagen\n");
    event_exit(data);
}