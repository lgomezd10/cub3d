/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:08:59 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 13:14:10 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/load_file.h"

void	load_color(char *line, t_game *data)
{
	char	**split;
	t_color	**color;
	char	*temp;

	color = 0;
	temp = ft_strdup(line);
	temp = ft_delete_set(&temp, " \t");
	split = ft_split_set(&temp[1], ",");
	if (!ft_strnstr(temp, ",,", ft_strlen(temp))
		&& ft_array_len((void **)split) == 3)
	{
		if (temp[0] == 'F')
			color = &data->floor;
		if (temp[0] == 'C')
			color = &data->ceiling;
		if (*color)
			handle_error(data, "Repeated configuration");
		save_color(data, color, split);
		free_split(&split);
		free(temp);
	}
	else
		handle_error(data, "Format to color must be X xxx,xxx,xxx");
}

int	load_texture(t_game *data, char **split)
{
	char	*texture;
	char	**opt;

	if (!split[1] || split[2])
		handle_error(data, "Invalid line for textures");
	texture = ft_strdup(split[1]);
	check_file(data, texture);
	opt = 0;
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
		handle_error(data, "Invalid line");
	if (*opt)
		handle_error(data, "Repeated texture configuration line");
	*opt = texture;
	return (1);
}

int	load_resolution(t_game *data, char **split)
{
	if (data->height && data->width)
		handle_error(data, "Repeated resolution configuration line");
	if (ft_array_len((void **)split) == 3)
	{
		if (ft_str_is_nbr(split[1]) && ft_str_is_nbr(split[2]))
		{
			data->width = ft_atoi(split[1]);
			data->height = ft_atoi(split[2]);
			if (data->height && data->width)
				return (1);
		}
	}
	handle_error(data, "Format to resolution R nbr1 nbr2");
	return (0);
}

int	load_line(int fd, char *line, t_game *data)
{
	char	**split;

	split = ft_split_set(line, " \t");
	if (ft_strlen(split[0]) > 2 || !ft_strncmp(split[0], "1", 1))
	{
		if (data_loaded(data))
			get_map_of_file(fd, line, data);
		else
			handle_error(data, "Invalid line");
	}
	else if (ft_strlen(split[0]) == 1)
	{
		if (!ft_strncmp(split[0], "F", 2) || !ft_strncmp(split[0], "C", 2))
			load_color(line, data);
		else if (!ft_strncmp(split[0], "S", 2))
			load_texture(data, split);
		else if (!ft_strncmp(split[0], "R", 2))
			load_resolution(data, split);
		else
			handle_error(data, "Invalid line");
	}
	else if (ft_strlen(split[0]) == 2)
		load_texture(data, split);
	free_split(&split);
	return (0);
}

int	load_file(t_game *data, char *file)
{
	int		fd;
	char	*line;
	int		noend;

	noend = 1;
	if (!name_file_ok(data, file))
		handle_error(data, "Invalid file name");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error(data, "Configuration file not found");
	while (noend > 0)
	{
		line = 0;
		noend = get_next_line(fd, &line);
		if (ft_strlen(line))
			load_line(fd, line, data);
		free(line);
	}
	return (0);
}
