/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:14:00 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 15:43:03 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_FILE_H
# define LOAD_FILE_H
# include "cub3d.h"

int		name_file_ok(t_game *data, char *file);
void	free_split(char ***split);
int		str_to_color(t_game *data, char *color);
void	save_color(t_game *data, t_color **color, char **split);
int		correct_line_map(char *str, t_game *data);
int		data_loaded(t_game *data);
int		get_map_of_file(int fd, char *str, t_game *data);
int		is_connected(t_game *data, int y, int x, int up);
int		check_connected(t_game *data, int y, int x, int right);
int		check_space(t_game *data, int y, int x);
#endif