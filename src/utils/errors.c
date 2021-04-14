/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:24:25 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/04/14 18:49:14 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_errors(char *msg)
{
	perror(msg);
	exit(0);
}

void	has_been_created(void *ptr)
{
	if (!ptr)
		ft_errors("Malloc return error");
}
