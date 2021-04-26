/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:24:25 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/26 19:33:28 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	handle_error(t_game *data, char *msg)
{
	free_components(data);
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(msg, 1);
	exit(1);
}

void	has_been_created(t_game *data, void *ptr)
{
	if (!ptr)
		handle_error(data, "Malloc return error");
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
