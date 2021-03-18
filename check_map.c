#include "cub3d.h"

t_point *new_point(int x, int y)
{
    t_point *point;
    point = (t_point *)ft_calloc(sizeof(t_point), 1);
    point->x = x;
    point->y = y;
    return (point);
}

t_point *update_point(t_point *point, int x, int y)
{
    point->x = x;
    point->y = y;
    return (point);
}

t_wall *get_points(t_file *data)
{
    t_wall *walls;
    int i;
    int j;
    char **table;

    table = data->table->table;
    walls = (t_wall *)ft_calloc(sizeof(t_wall), 1);
    i = 0;
    while (i < data->table->cols && ft_strrchr(" 1", table[0][i]))
    {
        if (table[0][i] == '1')
        {
            if (!walls->up_right)
                walls->up_right = new_point(0, i);
        
        if (!walls->up_left)
            walls->up_left = new_point(0, i);
        }
    }
    return (walls);
}
