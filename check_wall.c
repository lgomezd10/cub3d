#include "cub3d.h"

int check_adjacents_up(t_file *data, int y, int x)
{
    char **table;
    
    table = data->table->table;    
    if (y > (data->table->rows - 3))
    {
        printf("punto y: %d x %d\n", y, x);
        ft_errors("Los muros no estan conectados");
    }
    if (y < 0 || y >= data->table->rows || x < 0 || x >= data->table->cols)
        return (1);
    if (!ft_strchr("* 1", table[y][x]))
        ft_errors("Caracter incorrecto fuera del muro");
    else if (table[y][x] == '1' || table[y][x] == '*')
        return (1);
    else if (check_adjacents_up(data, y + 1, x) && check_adjacents_up(data, y, x - 1))
    {
        table[y][x] = '*';
        if (check_adjacents_up(data, y, x + 1))
            return (1);
    }
    ft_errors("El muro superior no está cerrado");
    return (0);
}

int check_adjacents_right(t_file *data, int y, int x)
{
    char **table;

    table = data->table->table;
    if (x < 2)
        ft_errors("Los muros no estan conectados");
    if (y < 0 || y >= data->table->rows || x < 0 || x >= data->table->cols)
        return (1);
    if (!ft_strchr("* 1", table[y][x]))
        ft_errors("Caracter incorrecto fuera del muro");
    else if (table[y][x] == '1' || table[y][x] == '*')
        return (1);
    else if (check_adjacents_right(data, y, x - 1) && check_adjacents_right(data, y - 1, x))
    {
        table[y][x] = '*';
        if (check_adjacents_right(data, y + 1, x))
            return (1);
    }
    ft_errors("El muro superior no está cerrado");
    return (0);
}

int check_adjacents_down(t_file *data, int y, int x)
{
    char **table;

    table = data->table->table;
    if (y < 2)
        ft_errors("Los muros no estan conectados");
    if (y < 0 || y >= data->table->rows || x < 0 || x >= data->table->cols)
        return (1);
    if (!ft_strchr("* 1", table[y][x]))
        ft_errors("Caracter incorrecto fuera del muro");
    else if (table[y][x] == '1' || table[y][x] == '*')
        return (1);
    else if (check_adjacents_down(data, y - 1, x) && check_adjacents_down(data, y, x + 1))
    {
        table[y][x] = '*';
        if (check_adjacents_down(data, y, x - 1))
            return (1);
    }
    ft_errors("El muro superior no está cerrado");
    return (0);
}

int check_adjacents_left(t_file *data, int y, int x)
{
    char **table;
    
    table = data->table->table;
    if (x > (data->table->cols - 3))
        ft_errors("Los muros no estan conectados");
    if (y < 0 || y >= data->table->rows || x < 0 || x >= data->table->cols)
        return (1);
    if (!ft_strchr("* 1", table[y][x]))
    {
        ft_errors("Caracter incorrecto fuera del muro");
    }
    else if (table[y][x] == '1' || table[y][x] == '*')
        return (1);
    else if (check_adjacents_left(data, y, x + 1) && check_adjacents_left(data, y + 1, x))
    {
        table[y][x] = '*';
        if (check_adjacents_left(data, y - 1, x))
            return (1);
    }
    ft_errors("El muro superior no está cerrado");
    return (0);
}



void check_walls(t_file *data)
{
    int i;
    
    i = 0;
     while (i < data->table->rows)
    {
        printf("comprobados adjacentes: %d\n", check_adjacents_left(data, data->table->rows - 1 - i, 0));
        print_struct(data);
        i++;
    }
    print_struct(data);
    
    
    i = 0;
    while (i < data->table->rows)
    {
        printf("comprobados adjacentes: %d\n", check_adjacents_right(data, i, data->table->cols - 1));
        i++;
    }
    print_struct(data);

   
    i = 0;
    while (i < data->table->cols)
    {
        printf("comprobados adjacentes: %d\n", check_adjacents_up(data, 0, i));        
        i++;
    }
    print_struct(data);
    
    i = 0;
    while (i < data->table->cols)
    {
        printf("comprobados adjacentes: %d\n", check_adjacents_down(data, data->table->rows - 1, data->table->cols - 1 - i));
        i++;
    }
    print_struct(data);
    
        //print_struct(data);
    
}