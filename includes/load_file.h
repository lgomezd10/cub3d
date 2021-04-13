#ifndef LOAD_FILE_H
# define LOAD_FILE_H
#include "cub3d.h"

int correct_line_map(char *str, t_game *data);
int data_loaded(t_game *data);
int get_map_of_file(int fd, char *str, t_game *data);
#endif