/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_closed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:25:22 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 15:15:50 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/load_file.h"

int	through_space(t_game *data, int y, int x)
{
	char	**table;

	table = data->table.table;
	if (x == 0 || ft_strchr("*1", table[y][x - 1]))
	{
		if (x == data->table.cols - 1 || ft_strchr(" 1", table[y][x + 1]))
		{
			while (x < data->table.cols && table[y][x] == ' '
				&& check_space(data, y, x))
				table[y][x++] = '*';
			if (x < data->table.cols && table[y][x] != '1')
				handle_error(data, "The wall is open");
			else if (x < data->table.cols && table[y][x] == '1')
				x = check_connected(data, y, x, 1);
			return (x);
		}
	}
	handle_error(data, "The wall is not closed");
	return (-1);
}

void	check_conexions(t_game *data, int y, int x)
{
	char	**table;

	table = data->table.table;
	if (table[y][x] == '2')
		add_new_sp_back(data, &data->sprites, x, y);
	if (ft_strchr("NSEW", table[y][x]))
	{
		load_player(data, x, y);
		table[y][x] = '0';
	}
	if (x == 0 && table[y][x] == '1')
		check_connected(data, y, x, 1);
	if (x == data->table.cols - 1 && table[y][x] == '1')
		check_connected(data, y, x, 0);
	if (x > 0 && table[y][x] == ' ' && table[y][x - 1] == '1')
		check_connected(data, y, x - 1, 0);
}

void	check_wall_closed(t_game *data)
{
	char	**table;
	int		i;
	int		j;

	table = data->table.table;
	i = 0;
	while (i < data->table.rows)
	{
		j = 0;
		while (j < data->table.cols)
		{
			check_conexions(data, i, j);
			if (table[i][j] == ' ')
				j = through_space(data, i, j);
			else
			{
				if (table[i][j] != '1' && (i == 0 || j == 0
					|| i == data->table.rows - 1 || j == data->table.cols - 1))
					handle_error(data, "The wall is not closed");
				j++;
			}
		}
		i++;
	}
}
