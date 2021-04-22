/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:25:15 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 14:18:02 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/load_file.h"

int	is_connected(t_game *data, int y, int x, int up)
{
	char	**table;
	int		connected;
	int		add;

	table = data->table.table;
	connected = y == 0;
	add = -1;
	if (!up)
	{
		connected = y == data->table.rows - 1;
		add = 1;
	}
	if (!connected)
	{
		if (x > 0)
			connected = table[y + add][x - 1] == '1';
		connected = connected || table[y + add][x] == '1';
		if (x < data->table.cols - 1)
			connected = connected || table[y + add][x + 1] == '1';
	}
	return (connected);
}

int	check_connected(t_game *data, int y, int x, int right)
{
	char	**table;
	int		conn_up;
	int		conn_down;
	int		i;
	int		add;

	conn_up = 0;
	conn_down = 0;
	table = data->table.table;
	i = x;
	add = 1;
	if (!right)
		add = -1;
	while ((!conn_down || !conn_up) && i < data->table.cols
		&& i >= 0 && table[y][i] == '1')
	{
		if (is_connected(data, y, i, 1))
			conn_up = 1;
		if (is_connected(data, y, i, 0))
			conn_down = 1;
		i += add;
	}	
	if (!conn_up || !conn_down)
		handle_error(data, "The wall is not connected");
	return (i);
}

int	check_space(t_game *data, int y, int x)
{
	int		up;
	int		right;
	int		down;
	int		left;
	char	**table;

	table = data->table.table;
	up = y == 0 || ft_strchr("*1", table[y - 1][x]);
	down = y == data->table.rows - 1 || ft_strchr(" 1", table[y + 1][x]);
	left = x == 0 || ft_strchr("*1", table[y][x - 1]);
	right = x == data->table.cols - 1 || ft_strchr(" 1", table[y][x + 1]);
	if (!up || !down || !left || !right)
		handle_error(data, "Forbidden spaces inside the wall");
	return (1);
}
