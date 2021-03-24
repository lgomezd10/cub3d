/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:18:02 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/24 17:43:26 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_str(void *str)
{
	char	*temp;

	temp = (char *)str;
	free(str);
}

void load_gamer(t_file *data, int y, int x, char pos)
{
	t_gamer *gamer;

	gamer = (t_gamer *)ft_calloc(sizeof(t_gamer), 1);
	if (!gamer)
		ft_errors("Error de memoria");
	gamer->unitHeight = data->height / data->table->rows;
	gamer->unitWidth = data->width / data->table->cols;
	gamer->position.x = x * gamer->unitWidth + (gamer->unitWidth / 2);
	gamer->position.y = y * gamer->unitHeight + (gamer->unitHeight / 2);
	if (pos == 'N')
	{
		gamer->direction.x = 0; 
		gamer->direction.y = -3; 
	}
	if (pos == 'S')
	{
		gamer->direction.x = 0; 
		gamer->direction.y = 3; 
	}
	if (pos == 'E')
	{
		gamer->direction.x = 3; 
		gamer->direction.y = 0; 
	}
	if (pos == 'W')
	{
		gamer->direction.x = -3; 
		gamer->direction.y = 0; 
	}
	data->gamer = gamer;	
}
