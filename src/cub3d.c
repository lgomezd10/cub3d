/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:55:32 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 11:23:22 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*data;

	data = 0;
	if (argc < 2 || argc > 3)
		handle_error(data, "Minimum one argument and maximum two");
	else
	{
		data = (t_game *)ft_calloc(sizeof(t_game), 1);
		has_been_created(data, data);
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 7))
				handle_error(data, "Second argument must be --save");
			data->to_save = 1;
			load_file(data, argv[1]);
			check_wall_closed(data);
			load_bmp(data);
		}
		else
		{
			load_file(data, argv[1]);
			check_wall_closed(data);
			run_game(data);
		}
	}
}
