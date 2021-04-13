#include "run_game.h"

// 54 + 4 * width * height

void save_as_char(unsigned char *str, int nbr)
{
    str[0] = (unsigned char)(nbr);
	str[1] = (unsigned char)(nbr >> 8);
	str[2] = (unsigned char)(nbr >> 16);
	str[3] = (unsigned char)(nbr >> 24);
}

void write_header(t_file *data, int fd)
{
    unsigned char *header;
    int *temp;
    int filesize;

    filesize = 54 + 4 * data->width * data->height;
    header = ft_calloc(sizeof(char), 54);
    has_been_created(header);
    header[0] = (unsigned char)('B');
    header[1] = (unsigned char)('M');
    save_as_char(&header[2], filesize);
    save_as_char(&header[10], 54);
    save_as_char(&header[14], 40);
    save_as_char(&header[18], data->width);
    save_as_char(&header[22], data->height);
    header[27] = (unsigned char)1;
    header[28] = (unsigned char)24;
    if (write(fd, header, 54) < 0)
        ft_errors("Error to write screenshop.bmp");
    free(header);
    header = 0;
}

void write_image(t_file *data)
{
    
}

int save_bmp(t_file *data)
{
    int fd;

    fd = open("screenshop.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND);
    if (fd < 0)
        ft_errors("Can't open screenshop.bmp");
    write_header(data, fd);

    close(fd);
}