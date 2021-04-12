/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:11:43 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/12 23:53:38 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"
#include <stdio.h>

static int	add_to_line(char **line, int diff)
{
	char	*temp;
	int		index;

	index = 0;
	temp = malloc(sizeof(*temp) * (ft_strlen(*line) + diff + 1));
	if (!temp)
		return (1);
	while ((*line)[index])
	{
		temp[index] = (*line)[index];
		index++;
	}
	while (--diff >= 0)
		temp[index++] = ' ';
	temp[index] = 0;
	free(*line);
	*line = temp;
	return (0);
}

static int	map_squarer(char ***map, int *x_max, int *y_max)
{
	int index;
	int diff;
	char **map_in;

	map_in = *map;
	*x_max = 0;
	*y_max = -1;
	while (map_in[++(*y_max)])
		if ((int)ft_strlen(map_in[*y_max]) > *x_max)
			*x_max = ft_strlen(map_in[*y_max]);
	index = -1;
	while (map_in[++index])
	{
		diff = *x_max - ft_strlen(map_in[index]);
		if (diff > 0)
		{
			if (add_to_line(&(map_in[index]), diff))
				return (1);
		}
	}
	return (0);
}

static int outer_validation(char **map, int x_max, int y_max)
{
	int x_index;
	int y_index;

	y_index = -1;
	while (map[++y_index])
	{
		x_index = 0;
		while (map[y_index][x_index])
		{
			if (!ft_strchr("1 ", map[y_index][x_index]))
				return (1);
			if (y_index == 0 || y_index == y_max - 1 || x_index == x_max - 1)
				x_index++;
			else
				x_index = x_max - 1;
		}
	}
	return (0);
}

int		map_validator(char ***map)
{
	int x_max;
	int y_max;

	x_max = 0;
	y_max = 0;
	if (map_squarer(map, &x_max, &y_max) || outer_validation(*map, x_max, y_max))
		return (1);
	return (0);
}
