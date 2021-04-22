/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:18:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/16 15:28:02 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_not_allowed(char c, int *orientation)
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

static int	add_line(char ***map, char *line)
{
	int		size;
	int		index;
	char	*new_line;
	char	**new_map;

	size = count_words(*map);
	new_map = malloc(sizeof(*new_map) * (size + 2));
	index = -1;
	while (++index < size)
		new_map[index] = (*map)[index];
	new_line = ft_strdup(line);
	if (!new_line)
	{
		free(new_map);
		return (1);
	}
	new_map[index++] = new_line;
	new_map[index] = NULL;
	free(*map);
	*map = new_map;
	return (0);
}

static int	check_line(char **line)
{
	int	orientation;
	int	index;

	index = 0;
	orientation = 0;
	while ((*line)[index])
		if (ft_not_allowed((*line)[index++], &orientation))
			return (1);
	return (0);
}

int			map_parser(char **line, t_des *description)
{
	char	**new;
	int		index;

	index = 0;
	if (check_line(line))
		return (1);
	if (!description->map)
	{
		new = ft_split(*line, 0);
		if (!new)
			return (1);
		description->map = new;
		return (0);
	}
	while (description->map[index])
		index++;
	return (add_line(&(description->map), *line));
}
