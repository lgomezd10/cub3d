#include "cub3d.h"

int follow_wall(t_file *data, int row, int col)
{
    char **table;
    int follow;

    table = data->table->table;
    follow = 0;
    if (row > 0)
    {
        follow = table[row - 1][col] == '1';
        if (col > 0)
            follow = follow || table[row - 1][col - 1] == '1';
        if (col < data->table->cols - 1)
            follow = follow || table[row - 1][col + 1] == '1';
    }
    else
        return (1);
    return (follow);
}

int build_map(t_list *list, t_file *data)
{
    char *line;
    int i;
    char **table;

    table = (char **)ft_calloc(sizeof(char *), data->table->rows);
    i = 0;
    while (table && list && i < data->table->rows)
    {
        table[i] = (char *)ft_calloc(sizeof(char), data->table->cols);
        ft_memset(table[i], ' ', data->table->cols);
        line = (char *)list->content;
        ft_memcpy(table[i], line, ft_strlen(line));        
        list = list->next;
        i++;
    }
    data->table->table = table;
    return (1);
}

int correct_line_map(char *str, t_file *data)
{
    int i;
    int hasone;

    i = 0;
    hasone = 0;
    if (str && str[i])
    {
        while (str[i] && ft_strrchr(" 012NSEW", str[i]))
        {
            if (str[i] == '1')
                hasone = 1;
            if (ft_strrchr("NSEW", str[i]))
            {
                if (!data->gamer_init)
                    data->gamer_init = str[i];
                else
                    ft_errors("Varios jugadores en el mapa");
            }
            i++;
        }
        if (!str[i] && hasone)
            return (1);
    }
    return (0);
}

int data_loaded(t_file *data)
{
    int out;

    out = data->t_NO && data->t_SO && data->t_WE && data->t_EA;
    out = out && data->floor && data->ceiling;
    out = out && data->sprite;
    out = out && data->height && data->width;
    return (out);
}

void	clear_list(t_list **list)
{
	t_list	*temp;
    char *str;

    temp = *list;
	while (*list)
    {
        temp = *list;
        free((char *)temp->content);
        temp->content = 0;
        *list = temp->next;
        free(temp);
    }
    *list = 0;
}

int get_map(int fd, char *str, t_file *data)
{
    int len;
    int noend;
    t_list *list;

    list = 0;
    noend = 1;
    if (!data->table)
        data->table = (t_table *)ft_calloc(sizeof(t_table), 1);
    len = ft_strlen(str);
    str = ft_strdup(str);
    while (noend >= 0 && str[0] && len && correct_line_map(str, data))
    {
        while (str[len - 1] == ' ')
            str[--len] = '\0';
        ft_lstadd_back(&list, ft_lstnew(str));
        if (data->table->cols < len)
            data->table->cols = len;
        data->table->rows++;        
        noend = get_next_line(fd, &str);
        len = ft_strlen(str);
    }
    if (!noend && data->gamer_init)
        build_map(list, data);
    else
        ft_errors("El mapa no es correcto");
    clear_list(&list);
    return (1);
}