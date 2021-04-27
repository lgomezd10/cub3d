/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:52:45 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/27 18:53:11 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*data;

	data = 0;
	if (argc < 2)
		handle_error(data, "Minimum one argument");
	else
	{
		data = (t_game *)ft_calloc(sizeof(t_game), 1);
		has_been_created(data, data);
		load_file(data, argv[1]);
		check_wall_closed(data);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
		{
			data->to_save = 1;
			load_bmp(data);
		}
		else
		{
			data->bonus.maps = argv;
			data->bonus.levels = argc - 1;
			data->bonus.level = 1;
			run_game(data);
		}
	}
}
