/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:19:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/09 00:00:16 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void init_description(t_des *to_fill)
{
	to_fill->x_res = 0;
	to_fill->y_res = 0;
	to_fill->no_path = NULL;
	to_fill->ea_path = NULL;;
	to_fill->so_path = NULL;;
	to_fill->we_path = NULL;;
	to_fill->s_path = NULL;;
	to_fill->floor_c = -2;
	to_fill->ceiling_c = -2;
	to_fill->map = NULL;
}

int cub_parser(int fd, t_des **to_fill)
{
	int	cnt_elems;
	char *line;
	char *identifiers = "RNOEASOWESFC";
	char *type;
	char *to_free;

	*to_fill = malloc(sizeof(**to_fill));
	if (!*to_fill)
		return (1);
	init_description(*to_fill);
	cnt_elems = 0;
	while (get_next_line(fd, &line) == 1 && cnt_elems < 8)
	{
		to_free = line;
		type = ft_strchr(identifiers, line[0]);
		if (!type && !ft_isspace(line[0]))
		{
			free(to_free);
			return (1);
		}
		if (&identifiers[0] == type)
		{
			cnt_elems++;
			if (resolution_parser(&line, *to_fill))
			{
				free(to_free);
				return (1);
			}
		}
		if (type < &identifiers[10] && type > &identifiers[0])
		{
			cnt_elems++;
			if (texture_parser(&line, *to_fill))
			{
				free(to_free);
				return (1);
			}
		}
		if (type ==  &identifiers[10] || type == &identifiers[11])
		{
			cnt_elems++;
			if (colour_parser(&line, *to_fill))
			{
				free(to_free);
				return (1);
			}
		}
		free(to_free);
	}
	free(line);
	return (0);
}
