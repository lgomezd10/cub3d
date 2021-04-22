/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:34:00 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/14 18:49:14 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

int	find_hit(t_game *data, t_view *view)
{	
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (view->sideDist.x < view->sideDist.y)
		{			
			view->sideDist.x += view->deltaDist.x;
			view->map.x += view->step_ray.x;
			view->side = 0;
		}
		else
		{
			view->sideDist.y += view->deltaDist.y;
			view->map.y += view->step_ray.y;
			view->side = 1;
		}
		if (!in_space_int(data, view->map.x, view->map.y))
			hit = 1;
	}
	return (view->side);
}

t_cont_img	*select_text(t_game *data, t_view *view)
{
	if (!view->side)
	{
		if (view->rayDir.x < 0)
			return (&data->text[North]);
		else
			return (&data->text[South]);
	}
	else
	{
		if (view->rayDir.y < 0)
			return (&data->text[West]);
		else
			return (&data->text[East]);
	}	
}
