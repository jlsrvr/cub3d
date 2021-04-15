/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:19:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/15 17:50:32 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	clean_fill(int result, int *cnt_elems, char *to_free)
{
	if (result)
	{
		free(to_free);
		return (1);
	}
	(*cnt_elems)++;
	return (0);
}

static int	dispatch_element(char **line, t_des *to_fill, int *cnt_elems)
{
	char *identifiers;
	char *to_free;
	char *type;

	to_free = *line;
	identifiers = "RNOEASOWESFC";
	type = ft_strchr(identifiers, (*line)[0]);
	if (!type && *line)
	{
		free(*line);
		return (1);
	}
	if (&identifiers[0] == type)
		if (clean_fill(resolution_parser(line, to_fill), cnt_elems, to_free))
			return (1);
	if (type < &identifiers[10] && type > &identifiers[0])
		if (clean_fill(texture_parser(line, to_fill), cnt_elems, to_free))
			return (1);
	if (type == &identifiers[10] || type == &identifiers[11])
		if (clean_fill(colour_parser(line, to_fill), cnt_elems, to_free))
			return (1);
	free(to_free);
	*line = NULL;
	return (0);
}

static int	dispatch_map(char *line, t_des **to_fill)
{
	int		line_check;
	char	*to_free;

	to_free = line;
	line_check = validate_map_line(line, *to_fill);
	if (!line_check)
		if (map_parser(&line, *to_fill))
		{
			free(to_free);
			return (1);
		}
	if (line_check == 1)
	{
		free(to_free);
		return (1);
	}
	free(to_free);
	return (0);
}

int			cub_parser(int fd, t_des **to_fill)
{
	int		gnl;
	int		cnt_elems;
	char	*line;

	if (init_description(to_fill))
		return (1);
	cnt_elems = 0;
	gnl = get_next_line(fd, &line);
	while (gnl == 1)
	{
		if (cnt_elems < 8)
		{
			if (dispatch_element(&line, *to_fill, &cnt_elems))
				return (1);
		}
		else if (dispatch_map(line, to_fill))
			return (1);
		gnl = get_next_line(fd, &line);
	}
	if (cnt_elems < 8)
		return (1);
	return (0);
}
