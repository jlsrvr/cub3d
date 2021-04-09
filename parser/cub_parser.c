/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:19:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/09 15:10:19 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static void	init_description(t_des *to_fill)
{
	to_fill->x_res = 0;
	to_fill->y_res = 0;
	to_fill->no_path = NULL;
	to_fill->ea_path = NULL;
	to_fill->so_path = NULL;
	to_fill->we_path = NULL;
	to_fill->s_path = NULL;
	to_fill->floor_c = -2;
	to_fill->ceiling_c = -2;
	to_fill->map = NULL;
}

static int	clean_fill(int result, int *cnt_elems, char **to_free)
{
	if (result)
	{
		free(*to_free);
		return (1);
	}
	(*cnt_elems)++;
	return (0);
}

static int	dispatch_line(char **line, t_des *to_fill, int *cnt_elems)
{
	char *to_free;
	char *identifiers;
	char *type;

	identifiers = "RNOEASOWESFC";
	to_free = *line;
	type = ft_strchr(identifiers, (*line)[0]);
	if (!type && *line)
	{
		free(to_free);
		return (1);
	}
	if (&identifiers[0] == type)
		if (clean_fill(resolution_parser(line, to_fill), cnt_elems, &to_free))
			return (1);
	if (type < &identifiers[10] && type > &identifiers[0])
		if (clean_fill(texture_parser(line, to_fill), cnt_elems, &to_free))
			return (1);
	if (type == &identifiers[10] || type == &identifiers[11])
		if (clean_fill(colour_parser(line, to_fill), cnt_elems, &to_free))
			return (1);
	free(to_free);
	return (0);
}

int			cub_parser(int fd, t_des **to_fill)
{
	int		cnt_elems;
	char	*line;

	*to_fill = malloc(sizeof(**to_fill));
	if (!*to_fill)
		return (1);
	init_description(*to_fill);
	cnt_elems = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (cnt_elems < 8)
		{
			if (dispatch_line(&line, *to_fill, &cnt_elems))
				return (1);
		}
		else
		{
			if (map_parser(&line, *to_fill))
				return (1);
		}
	}
	free(line);
	return (0);
}
