#ifndef CUB3D_H
#define CUB3D_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} t_color;

typedef struct s_table
{
    int cols;
    int rows;
    char **table;
}   t_table;

typedef struct s_file
{
    int width;
    int height;
    char gamer;
    char *t_NO;
    char *t_SO;
    char *t_WE;
    char *t_EA;
    char *sprite;
    t_color *floor;
    t_color *ceiling;
    t_table *table;
} t_file;

char	**ft_split_set(char const *s, char *set);
int ft_array_len(char **a);
int ft_is_nbr(char *str);
char *ft_delete_set(char **str, char *set);
int load_file(char *file, t_file *data);
void ft_errors(char *msg);
int correct_line_map(char *str, t_file *data);
int data_loaded(t_file *data);
int get_map(int fd, char *str, t_file *data);
#endif