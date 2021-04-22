/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:09:23 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 13:20:15 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/load_file.h"

int	name_file_ok(t_game *data, char *file)
{
	int	len;
	int	i;

	len = ft_strlen(file);
	i = len - 4;
	if (!ft_strncmp(&file[i], ".cub", 4))
	{
		check_file(data, file);
		return (1);
	}
	return (0);
}

void	free_split(char ***split)
{
	int	i;

	i = 0;
	if (split && *split)
	{
		while ((*split)[i])
		{
			free((*split)[i]);
			(*split)[i] = 0;
			i++;
		}
	}
	free(*split);
	*split = 0;
}

int	str_to_color(t_game *data, char *color)
{
	int	nbr;

	if (ft_str_is_nbr(color))
	{
		nbr = ft_atoi(color);
		if (nbr >= 0 && nbr <= 255)
			return (nbr);
	}
	handle_error(data, "Color must be between 0 y 255");
	return (-1);
}

void	check_file(t_game *data, char *file)
{
	int		fd;
	char	*msg;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		msg = ft_strjoin("Error to open file: ", file);
		handle_error(data, msg);
	}
	close(fd);
}

void	save_color(t_game *data, t_color **color, char **split)
{
	*color = (t_color *)ft_calloc(sizeof(t_color), 1);
	has_been_created(data, *color);
	(*color)->red = str_to_color(data, split[0]);
	(*color)->green = str_to_color(data, split[1]);
	(*color)->blue = str_to_color(data, split[2]);
}
