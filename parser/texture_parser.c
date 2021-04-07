/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:55:11 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/07 16:55:25 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	fill_des(char ***dest, int index, char *str)
{
	char *new;
	int ret;

	ret = 0;
	new = ft_strdup(str);
	if (!new)
		ret = 1;
	*(dest[index]) = new;
	free(dest);
	return (ret);
}

static char ***build_dest(t_des *description)
{
	char ***dest;

	dest = malloc(sizeof(char*) * 5);
	if (!dest)
		return (NULL);
	dest[0] = &(description->no_path);
	dest[1] = &(description->ea_path);
	dest[2] = &(description->so_path);
	dest[3] = &(description->we_path);
	dest[4] = &(description->s_path);
	return (dest);
}

int	texture_parser(char **line, t_des *description)
{
	int index;
	char ***dest;
	char identifiers[5][3] = {"NO", "EA", "SO", "WE", "S"};

	dest = build_dest(description);
	if (!dest)
		return (1);
	index = -1;
	skip_space(line);
	while (++index < 5)
	{
		if (ft_strnstr(*line, identifiers[index], 2))
			break ;
	}
	(*line)++;
	if (index != 4)
		(*line)++;
	skip_space(line);
	if (*(dest[index]))
	{
		fill_des(dest, index, "|duplicate|");
		return (1);
	}
	return (fill_des(dest, index, *line));
}
