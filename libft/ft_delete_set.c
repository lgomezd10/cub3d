/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:39:09 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/17 15:41:11 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_delete_set(char **str, char *set)
{
	char	*copy;
	char	*str;
	int		len;
	int		i;
	int		j;

	str = *str;
	len = ft_strlen(str);
	copy = ft_calloc(sizeof(char), len + 1);
	copy[len] = '\0';
	if (copy)
	{
		i = 0;
		j = 0;
		while (i < len && str[i])
		{
			if (!ft_strrchr(set, str[i]))
				copy[j++] = str[i];
			i++;
		}
		free(*str);
		*str = ft_strdup(copy);
		free(copy);
	}
	return (str);
}
