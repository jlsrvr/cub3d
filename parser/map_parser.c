/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:18:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/10 17:55:30 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

//0, 1, 2, and one of the following N, E, S or W

static int ft_not_allowed(char c, int *orientation)
{
	if (ft_isspace(c) || ft_strchr("012", c))
		return (0);
	if (ft_strchr("NESW", c) && *orientation == 0)
	{
		*orientation = 1;
		return (0);
	}
	return (1);
}

int map_parser(char **line, t_des *description)
{
	char **new;
	int index;
	int orientation;

	index = 0;
	orientation = 0;
	while ((*line)[index])
		if (ft_not_allowed((*line)[index++], &orientation))
			return (1);
	new = ft_split(*line, 'e');
	description->map = new;
	return (0);
}
