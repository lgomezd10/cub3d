#include "cub3d.h"

int is_conect(t_file *data, int y, int x)
{
    char **table;

    table = data->table->table;
    if (table[y-1][x-1] == '1' || table[y-1][x] == '1' || table[y+1] == '1')
        return (1);
    return (0);
}

int wall_conected(t_file *data)
{
    char **table;
    int i;
    int j;
    int connected;

    table = data->table->table;
    i = 1;    
    connected = 0;
    while (i < data->table->rows - 1)
    {
        j = 0;
        while (j < data->table->cols - 3 && table[i][j] == ' ')
        {
            table[i][j] = '*';
            j++;
        }
        if (table[i][j] != '1')
            ft_errors("el mapa tiene el muro abierto");
        while (!connected && table[i][j] == '1' && j < data->table->cols - 1)
        {
            if (is_conect(table, i, j))
                connected = 1;
            table[i][j] = '1';
            j++;
        }
        if (!connected)
            ft_errors("El muro no está conectado");        
        j = data->table->cols - 1;
        while (j >= 0 && table[i][j] == ' ')
        {
            table[i][j] = '*';
            j--;
        }
        if (table[i][j] != '1')
            ft_errors("el mapa tiene el muro abierto");
        while (!connected && table[i][j] == '1' && j >= 0)
        {
            if (is_conect(table, i, j))
                connected = 1;
            table[i][j] = '1';
            j--;
        }
        if (!connected)
            ft_errors("El muro no está conectado");
    }
    
}