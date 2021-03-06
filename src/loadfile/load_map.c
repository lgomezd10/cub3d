/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:47:48 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/21 13:20:46 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	build_map(t_list *list, t_game *data, int noend)
{
	char	*line;
	int		i;
	char	**table;

	if (!noend && data->player_init)
	{
		table = (char **)ft_calloc(sizeof(char *), data->table.rows);
		has_been_created(data, table);
		i = 0;
		while (table && list && i < data->table.rows)
		{
			table[i] = (char *)ft_calloc(sizeof(char), data->table.cols);
			has_been_created(data, table[i]);
			ft_memset(table[i], ' ', data->table.cols);
			line = (char *)list->content;
			ft_memcpy(table[i], line, ft_strlen(line));
			list = list->next;
			i++;
		}
		data->table.table = table;
		return (1);
	}
	handle_error(data, "Map is not correct");
	return (0);
}

int	correct_line_map(char *str, t_game *data)
{
	int	i;
	int	hasone;

	i = 0;
	hasone = 0;
	if (str && str[i])
	{
		while (str[i] && ft_strrchr(" 012NSEW", str[i]))
		{
			if (str[i] == '1')
				hasone = 1;
			if (ft_strrchr("NSEW", str[i]))
			{
				if (!data->player_init)
					data->player_init = str[i];
				else
					handle_error(data, "More than one player on the map");
			}
			i++;
		}
		if (!str[i] && hasone)
			return (1);
	}
	return (0);
}

int	data_loaded(t_game *data)
{
	int	out;

	out = data->t_NO && data->t_SO && data->t_WE && data->t_EA;
	out = out && data->floor && data->ceiling;
	out = out && data->sprite;
	out = out && data->height && data->width;
	return (out);
}

void	clear_list(t_list **list)
{
	t_list	*temp;
	char	*str;

	while (*list)
	{
		temp = *list;
		str = temp->content;
		free(str);
		temp->content = 0;
		*list = temp->next;
		free(temp);
	}
	*list = 0;
}

int	get_map_of_file(int fd, char *str, t_game *data)
{
	int		len;
	int		noend;
	t_list	*list;

	list = 0;
	noend = 1;
	len = ft_strlen(str);
	str = ft_strdup(str);
	has_been_created(data, str);
	while (noend >= 0 && str[0] && len && correct_line_map(str, data))
	{
		while (str[len - 1] == ' ')
			str[--len] = '\0';
		ft_lstadd_back(&list, ft_lstnew(str));
		if (data->table.cols < len)
			data->table.cols = len;
		data->table.rows++;
		str = 0;
		noend = get_next_line(fd, &str);
		len = ft_strlen(str);
	}
	free(str);
	build_map(list, data, noend);
	clear_list(&list);
	return (1);
}
