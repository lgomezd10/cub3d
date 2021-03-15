#include "cub3d.h"

int get_color(char *color)
{
    int nbr;

    if (ft_is_nbr(color))
    {
        nbr = ft_atoi(color);
        if (nbr >= 0 && nbr <= 255)
            return (nbr);
    }
    return (-1);
}

int load_color(char *line, t_file *data)
{
    char **split;
    t_color **color;

    color = 0;
    line = ft_delete_set(&line, " \t");
    split = ft_split(&line[1], ',');
    if (ft_array_len(split) != 3)
        ft_errors("Error formato* color");
    if (line[0] == 'F')
        color = &data->floor;
    if (line[0] == 'C')
        color = &data->ceiling;
    if (*color)
        ft_errors("LInea repetida");
    *color = (t_color *)ft_calloc(sizeof(t_color), 1);
    if (*color)
    {
        (*color)->red = get_color(split[0]);
        (*color)->green = get_color(split[1]);
        (*color)->blue = get_color(split[1]);
        if ((*color)->red >= 0 && (*color)->green >= 0 &&
        (*color)->blue >= 0)
        {
            
            return (1);
        }
    }
    ft_errors("El formato para color es X xxx,xxx,xxx");
}

int load_texture(char **split, t_file *data)
{
    char *texture;
    char **opt;

    texture = split[1];
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

int load_line(char *line, t_file *data)
{
    char **split;

    split = ft_split_set(line, " \t");
    if (ft_strlen(split[0]) > 2)
    {
        //TODO comprobar si es mapa solo si se ha cargado todo
        ft_errors("Linea no válida");
    }
    else if (ft_strlen(split[0]) == 1)
    {
        if (!ft_strncmp(split[0], "F", 1) || !ft_strncmp(split[0], "C", 1))
            load_color(line, data);
        if (!ft_strncmp(split[0], "S", 1)) //color
            load_texture(split, data);
    }
    else if (ft_strlen(split[0]) == 2)
    {
        load_texture(split, data);
    }
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
    if (!name_file_ok(file))
        ft_errors("Nombre de fichero inválido");
    fd = open(file, O_RDONLY);
    if (fd < 0)
        ft_errors("No se puede abrir el archivo");
    line = 0;
    while (noend > 0)
    {
        free(line);
        line = 0;
        noend = get_next_line(fd, &line);
        if (ft_strlen(line))
        {
            printf("COMProbando %s\n", line);
            load_line(line, data);
        }
    }

}