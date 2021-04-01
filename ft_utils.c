/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:18:02 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/01 14:47:32 by lgomez-d         ###   ########.fr       */
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
	gamer->position.x = x + 0.5;
	gamer->position.y = y + 0.5;
	printf("llega a antes\n");
	if (data->gamer_init == 'N')
    {
        set_point(&gamer->direction, 0, -1);
        set_point(&gamer->plane, 0.66, 0.0);
    }
    if (data->gamer_init == 'S')
    {
        set_point(&gamer->direction, 0, 1);
        set_point(&gamer->plane, -0.66, 0.0);
    }
    if (data->gamer_init == 'W')
    {
        set_point(&gamer->direction, -1, 0);
        set_point(&gamer->plane, 0, -0.66);
    }
    if (data->gamer_init == 'E')
    {
        set_point(&gamer->direction, 1, 0);
        set_point(&gamer->plane, 0, 0.66);
    }

	data->gamer = gamer;	
}
