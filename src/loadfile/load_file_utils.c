/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:09:23 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/19 17:10:17 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/load_file.h"

int	name_file_ok(char *file)
{
	int	len;
	int	i;

	len = ft_strlen(file);
	i = len - 4;
	if (!ft_strncmp(&file[i], ".cub", 4))
	{
		check_file(file);
		return (1);
	}
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = 0;
			i++;
		}
	}
}

int	str_to_color(char *color)
{
	int	nbr;

	if (ft_str_is_nbr(color))
	{
		nbr = ft_atoi(color);
		if (nbr >= 0 && nbr <= 255)
			return (nbr);
	}
	ft_errors("Color must be between 0 y 255");
	return (-1);
}

void	check_file(char *file)
{
	int		fd;
	char	*msg;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		msg = ft_strjoin("Error to open file: ", file);
		ft_errors(msg);
	}
	close(fd);
}

void	save_color(t_color **color, char **split)
{
	*color = (t_color *)ft_calloc(sizeof(t_color), 1);
	has_been_created(*color);
	(*color)->red = str_to_color(split[0]);
	(*color)->green = str_to_color(split[1]);
	(*color)->blue = str_to_color(split[2]);
}
