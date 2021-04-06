#include "cub3d.h"

void print_struct(t_file *data)
{
    int i;
    int j;
    /*
    printf("NO: %s\n", data->t_NO);
    printf("SO: %s\n", data->t_SO);
    printf("WE: %s\n", data->t_WE);
    printf("EA: %s\n", data->t_EA);
    if (data->floor)
        printf("FLOOR: %d %d %d\n", data->floor->red, data->floor->green, data->floor->blue);
    if (data->ceiling)
        printf("ceiling: %d %d %d\n", data->ceiling->red, data->ceiling->green, data->ceiling->blue);
    printf("SPRITE: %s\n", data->sprite);
    */
    if (data->table && data->table->table)
    {
        i = 0;
        printf("filas %d col %d\n", data->table->rows, data->table->cols);
        while (i < data->table->rows)
        {
            j = 0;
            while (j < data->table->cols)
            {
               printf("%c ", data->table->table[i][j]);
               j++;
            }
            //free(data->table->table[i]);
            printf("\n");
            i++;
        }
        //free(data->table->table);
    }
}

int main(int argc, char **argv)
{
    
    t_file data;

    ft_bzero(&data, sizeof(t_file));
    print_struct(&data);
    if (argc < 2 || argc > 3)
        ft_errors("Solo se permiten dos argumentos");
    else
    {
        load_file(argv[1], &data);
        print_struct(&data);
        wall_connected(&data);
        print_struct(&data);
        printf("segunda impresión\n");
        print_image(&data);
        system("leaks cub3d");
    }
}