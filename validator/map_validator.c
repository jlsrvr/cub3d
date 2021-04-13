/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:11:43 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/13 13:07:21 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

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
	int		index;
	int		diff;
	char	**map_in;

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

static int	outer_validation(char **map, int x_max, int y_max)
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
			if (y_index == 0 || y_index == y_max - 1 || x_index == (x_max - 1))
				x_index++;
			else
				x_index = (x_max - 1);
		}
	}
	return (0);
}

static int	check_surrounding(char **map, int pos_x, int pos_y, int *pos_cnt)
{
	int		temp_x;
	int		temp_y;
	char	*allowed;

	if (map[pos_y][pos_x] == '1')
		return (0);
	if (map[pos_y][pos_x] == ' ')
		allowed = "1 ";
	else if (ft_strchr("02NESW", map[pos_y][pos_x]))
	{
		allowed = "012NESW";
		if (ft_strchr("NESW", map[pos_y][pos_x]))
			(*pos_cnt)++;
	}
	if (*pos_cnt > 1)
		return (1);
	temp_y = (pos_y - 2);
	while (++temp_y < (pos_y + 2))
	{
		temp_x = (pos_x - 2);
		while (++temp_x < (pos_x + 2))
			if (!ft_strchr(allowed, map[temp_y][temp_x]))
				return (1);
	}
	return (0);
}

int			map_validator(char ***map)
{
	int x_max;
	int y_max;
	int x_index;
	int y_index;
	int pos_cnt;

	x_max = 0;
	y_max = 0;
	pos_cnt = 0;
	if (map_squarer(map, &x_max, &y_max))
		return (1);
	if (outer_validation(*map, x_max, y_max))
		return (1);
	y_index = 0;
	while (++y_index < (y_max - 1))
	{
		x_index = 0;
		while (++x_index < (x_max - 1))
			if (check_surrounding(*map, x_index, y_index, &pos_cnt))
				return (1);
	}
	if (pos_cnt != 1)
		return (1);
	replace_spaces(map);
	return (0);
}
