#include "includes/cub3d.h"

void print_struct(t_game *data)
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
    if (data->table.table)
    {
        i = 0;
        printf("filas %d col %d\n", data->table.rows, data->table.cols);
        while (i < data->table.rows)
        {
            j = 0;
            while (j < data->table.cols)
            {
               printf("%c ", data->table.table[i][j]);
               j++;
            }
            //free(data->table.table[i]);
            printf("\n");
            i++;
        }
        //free(data->table.table);
    }
}

int main(int argc, char **argv)
{
    t_game *data;

    data = 0;
    //system("leaks cub3D"); 
    if (argc < 2 || argc > 3)
        ft_errors("Solo se permiten dos argumentos");
    else
    {
        data = (t_game *)ft_calloc(sizeof(t_game), 1);
        has_been_created(data);
        if (argc == 3)
        {
            if (ft_strncmp(argv[2], "--save", 6))
                ft_errors("If there are second argument it must be --save");
            data->to_save = 1;
            load_file(argv[1], data);
            check_wall_closed(data);
            printf("Se va a cargar la imagen\n");
            print_struct(data);
            load_bmp(data);
        }
        else
        {
            //print_struct(data);
            load_file(argv[1], data);
            //print_struct(data);
            check_wall_closed(data);
            //print_struct(data);
            //printf("segunda impresión\n");
            run_game(data);
            //system("leaks cub3D");
        }
    }
}