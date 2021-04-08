/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:19:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/08 18:12:14 by jrivoire         ###   ########.fr       */
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
	char *line;
	char *identifiers = "RNOEASOWESFC";

	*to_fill = malloc(sizeof(**to_fill));
	if (!*to_fill)
		return (1);
	init_description(*to_fill);
	// The first or first two char of a line are neccesarily it's identifier
	return (0);
}
