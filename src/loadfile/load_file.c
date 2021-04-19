/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:08:59 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/19 17:32:03 by lgomez-d         ###   ########.fr       */
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
			ft_errors("Repeated configuration");
		save_color(color, split);
		free_split(split);
		free(split);
		free(temp);
	}
	else
		ft_errors("Format to color must be X xxx,xxx,xxx");
}

int	load_texture(char **split, t_game *data)
{
	char	*texture;
	char	**opt;

	if (!split[1] || split[2])
		ft_errors("Invalid line for textures");
	texture = ft_strdup(split[1]);
	check_file(texture);
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
		ft_errors("Invalid line");
	if (*opt)
		ft_errors("Repeated texture configuration line");
	*opt = texture;
	return (1);
}

int	load_resolution(char **split, t_game *data)
{
	if (data->height && data->width)
		ft_errors("Repeated resolution configuration line");
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
	ft_errors("Format to resolution R nbr1 nbr2");
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
			ft_errors("Invalid line");
	}
	else if (ft_strlen(split[0]) == 1)
	{
		if (!ft_strncmp(split[0], "F", 1) || !ft_strncmp(split[0], "C", 1))
			load_color(line, data);
		else if (!ft_strncmp(split[0], "S", 1))
			load_texture(split, data);
		else if (!ft_strncmp(split[0], "R", 1))
			load_resolution(split, data);
	}
	else if (ft_strlen(split[0]) == 2)
		load_texture(split, data);
	free_split(split);
	free(split);
	split = 0;
	return (0);
}

int	load_file(char *file, t_game *data)
{
	int		fd;
	char	*line;
	int		noend;

	noend = 1;
	if (!name_file_ok(file))
		ft_errors("Invalid file name");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_errors("Configuration file not found");
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
