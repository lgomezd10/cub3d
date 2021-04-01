#include "cub3d.h"

void free_split(char **split)
{
    int i;

    i = 0;
    if (split)
    {
        while (split[i])
        {
            free(split[i]);
            split[i] = 0;
            i++;
        }
    }
}

int get_color(char *color)
{
    int nbr;
    if (ft_str_is_nbr(color))
    {
        nbr = ft_atoi(color);
        if (nbr >= 0 && nbr <= 255)
            return (nbr);
    }
    ft_errors("El color puede estar entre 0 y 255");
    return (-1);
}

int load_color(char *line, t_file *data)
{
    char **split;
    t_color **color;
    char *temp;

    color = 0;
    temp = ft_strdup(line);
    temp = ft_delete_set(&temp, " \t");
    split = ft_split_set(&temp[1], ",");
    if (ft_array_len((void **)split) == 3)
    {
        if (temp[0] == 'F')
            color = &data->floor;
        if (temp[0] == 'C')
            color = &data->ceiling;
        if (*color)
            ft_errors("Linea repetida");
        *color = (t_color *)ft_calloc(sizeof(t_color), 1);
        if (*color)
        {
            (*color)->red = get_color(split[0]);
            (*color)->green = get_color(split[1]);
            (*color)->blue = get_color(split[2]);
            free_split(split);
            free(split);
            free(temp);
            return (1);
        }
    }
    ft_errors("El formato para color es X xxx,xxx,xxx");
    return (0);
}

int load_texture(char **split, t_file *data)
{
    char *texture;
    char **opt;

    texture = ft_strdup(split[1]);
    opt = 0;
    //TODO intentar abrir el fichero
    if (!ft_strncmp(split[0], "NO", 3))
        opt = &data->t_NO;
    else if (!ft_strncmp(split[0], "SO", 3))
        opt = &data->t_SO;
    else if (!ft_strncmp(split[0], "WE", 3))
        opt = &data->t_WE;
    else if (!ft_strncmp(split[0], "EA", 3))
        opt = &data->t_EA;
    else if (!ft_strncmp(split[0], "S", 3))
        opt = &data->sprite;
    else
        ft_errors("Opción no valida");
    if (*opt)
        ft_errors("Opcion repetida");
    *opt = texture;
    return (1);
}

int load_resolution(char **split, t_file *data)
{
    if (data->height && data->width)
        ft_errors("Resolución repetida");
    if (ft_array_len((void **)split) == 3)
    {
        if (ft_str_is_nbr(split[1]) && ft_str_is_nbr(split[2]))
            data->width = ft_atoi(split[1]);
            data->height = ft_atoi(split[2]);
            if (data->height && data->width)
                return (1);
    }
    ft_errors("Formato para resoltion R nbr1 nbr2");
    return (0);
}

int load_line(int fd, char *line, t_file *data)
{
    char **split;

    split = ft_split_set(line, " \t");
    if (ft_strlen(split[0]) > 2)
    {
        if (data_loaded(data))
            get_map(fd, line, data);
        else
            ft_errors("Linea no válida");
    }
    else if (ft_strlen(split[0]) == 1)
    {
        if (!ft_strncmp(split[0], "F", 1) || !ft_strncmp(split[0], "C", 1))
            load_color(line, data);
        else if (!ft_strncmp(split[0], "S", 1))
            load_texture(split, data);
        else if (!ft_strncmp(split[0], "R", 1))
            load_resolution(split, data);
    }
    else if (ft_strlen(split[0]) == 2)
        load_texture(split, data);
    free_split(split);
    free(split);
    split = 0;
    return (0);
}

int name_file_ok(char *file)
{
    int len;
    int i;

    len = ft_strlen(file);
    i = len - 4;
    if (!ft_strncmp(&file[i], ".cub", 4))
        return (1);
    return (0);
}

int load_file(char *file, t_file *data)
{
    int fd;
    char *line;
    int noend;

    noend = 1;
    data->opt.mov_speed = 0.11;
    data->opt.rot_speed = 0.11;
    if (!name_file_ok(file))
        ft_errors("Nombre de fichero inválido");
    fd = open(file, O_RDONLY);
    if (fd < 0)
        ft_errors("No se puede abrir el archivo");
    line = 0;
    while (noend > 0 || (line && *line))
    {        
        noend = get_next_line(fd, &line);
        if (ft_strlen(line))
            load_line(fd, line, data);
        free(line);
        line = 0;
    }
    return (0);
}